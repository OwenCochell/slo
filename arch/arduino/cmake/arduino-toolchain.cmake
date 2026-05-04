# Arduino CMake toolchain driven by arduino-cli.
#
# Inputs (cache or env):
#   ARDUINO_FQBN                   fully-qualified board name, e.g.
#                                  "arduino:avr:uno" or with options
#                                  "arduino:avr:nano:cpu=atmega168"
#   ARDUINO_CLI                    path to arduino-cli (else searched in PATH)
#   ARDUINO_USE_SYSTEM_TOOLCHAIN   ON: use avr-gcc/avr-g++/etc. from PATH
#                                  instead of the (often old) compiler bundled
#                                  with the Arduino platform. Lets you escape
#                                  Arduino AVR's GCC 7.3.0 pin and compile
#                                  C++20+ code. Default OFF (use bundled).
#
# Exposed cache variables (for downstream modules):
#   ARDUINO_FQBN, ARDUINO_CORE_PATH, ARDUINO_VARIANT_PATH,
#   ARDUINO_PLATFORM_PATH, ARDUINO_PROP_<key with dots → __>
#
# Adds <this dir>/modules to CMAKE_MODULE_PATH so consumers can
#   include(ArduinoCore)
#   include(ArduinoHelpers)

include_guard(GLOBAL)

if(NOT DEFINED ARDUINO_FQBN AND DEFINED ENV{ARDUINO_FQBN})
  set(ARDUINO_FQBN "$ENV{ARDUINO_FQBN}")
endif()
if(NOT ARDUINO_FQBN)
  set(ARDUINO_FQBN "arduino:avr:uno")
  message(STATUS "ARDUINO_FQBN not set, defaulting to ${ARDUINO_FQBN}")
endif()
set(ARDUINO_FQBN "${ARDUINO_FQBN}" CACHE STRING "Arduino fully-qualified board name" FORCE)

if(NOT ARDUINO_CLI)
  find_program(ARDUINO_CLI arduino-cli REQUIRED)
endif()

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

execute_process(
  COMMAND "${ARDUINO_CLI}" board details --fqbn "${ARDUINO_FQBN}" --format json
  OUTPUT_VARIABLE _arduino_json
  ERROR_VARIABLE  _arduino_err
  RESULT_VARIABLE _arduino_rc
)
if(NOT _arduino_rc EQUAL 0)
  message(FATAL_ERROR
    "arduino-cli board details failed for FQBN '${ARDUINO_FQBN}':\n${_arduino_err}\n"
    "Is the platform installed?  Try: arduino-cli core install <packager>:<arch>")
endif()

string(JSON _bp_count ERROR_VARIABLE _bp_err LENGTH "${_arduino_json}" build_properties)
if(_bp_err OR NOT _bp_count OR _bp_count EQUAL 0)
  message(FATAL_ERROR "arduino-cli returned no build_properties for ${ARDUINO_FQBN}")
endif()

math(EXPR _last "${_bp_count} - 1")
foreach(_i RANGE 0 ${_last})
  string(JSON _kv GET "${_arduino_json}" build_properties ${_i})
  if(_kv MATCHES "^([^=]+)=(.*)$")
    set(_key "${CMAKE_MATCH_1}")
    set(_val "${CMAKE_MATCH_2}")
    string(REPLACE "." "__" _safe "${_key}")
    set(ARDUINO_PROP_${_safe} "${_val}")
  endif()
endforeach()

if(NOT DEFINED ARDUINO_PROP_compiler__path)
  message(FATAL_ERROR "arduino-cli output missing compiler.path for ${ARDUINO_FQBN}")
endif()

set(CMAKE_SYSTEM_PROCESSOR "${ARDUINO_PROP_build__arch}")

option(ARDUINO_USE_SYSTEM_TOOLCHAIN
  "Use avr-gcc/g++/etc. from PATH instead of the version bundled with Arduino" OFF)

# Resolve a tool to either the bundled location or the system PATH.
# Always sets <out_var> in the cache (FORCE) so toggling the option re-resolves.
function(_arduino_resolve_tool out_var cmd)
  if(ARDUINO_USE_SYSTEM_TOOLCHAIN)
    find_program(_found "${cmd}" NO_CACHE)
    if(NOT _found)
      message(FATAL_ERROR
        "ARDUINO_USE_SYSTEM_TOOLCHAIN=ON but '${cmd}' was not found in PATH")
    endif()
    set(${out_var} "${_found}" CACHE FILEPATH "" FORCE)
  else()
    set(${out_var} "${ARDUINO_PROP_compiler__path}${cmd}" CACHE FILEPATH "" FORCE)
  endif()
endfunction()

_arduino_resolve_tool(CMAKE_C_COMPILER   "${ARDUINO_PROP_compiler__c__cmd}")
_arduino_resolve_tool(CMAKE_CXX_COMPILER "${ARDUINO_PROP_compiler__cpp__cmd}")
_arduino_resolve_tool(CMAKE_ASM_COMPILER "${ARDUINO_PROP_compiler__c__cmd}")
_arduino_resolve_tool(CMAKE_AR           "${ARDUINO_PROP_compiler__ar__cmd}")
_arduino_resolve_tool(CMAKE_OBJCOPY      "${ARDUINO_PROP_compiler__objcopy__cmd}")
if(DEFINED ARDUINO_PROP_compiler__size__cmd)
  _arduino_resolve_tool(CMAKE_SIZE_UTIL  "${ARDUINO_PROP_compiler__size__cmd}")
endif()

# Derive ranlib alongside ar (Arduino doesn't expose it directly). With LTO,
# both must be the gcc wrappers so the LTO plugin gets loaded for archive
# creation and indexing.
string(REGEX REPLACE "-ar$" "-ranlib" _ranlib "${ARDUINO_PROP_compiler__ar__cmd}")
_arduino_resolve_tool(CMAKE_RANLIB "${_ranlib}")
unset(_ranlib)

# Strip per-action flags that CMake's compile rule supplies itself:
#   -c   (CMake adds it for compile, must NOT appear in CXX_FLAGS or it
#         leaks into the link rule and breaks linking)
#   -MMD (CMake adds its own -MD/-MT/-MF for dep tracking)
function(_arduino_recipe_to_flags recipe out_var)
  set(f "${recipe}")
  string(REGEX REPLACE "^\"[^\"]+\"[ \t]+" "" f "${f}")
  string(REGEX REPLACE "[ \t]+\\{includes\\}.*$" "" f "${f}")
  string(REGEX REPLACE "(^| )-c( |$)" " " f "${f}")
  string(REGEX REPLACE "(^| )-MMD( |$)" " " f "${f}")
  string(REGEX REPLACE "[ \t]+" " " f "${f}")
  string(STRIP "${f}" f)
  set(${out_var} "${f}" PARENT_SCOPE)
endfunction()

_arduino_recipe_to_flags("${ARDUINO_PROP_recipe__c__o__pattern}"   _c_flags)
_arduino_recipe_to_flags("${ARDUINO_PROP_recipe__cpp__o__pattern}" _cxx_flags)
_arduino_recipe_to_flags("${ARDUINO_PROP_recipe__S__o__pattern}"   _asm_flags)

set(CMAKE_C_FLAGS_INIT   "${_c_flags}")
set(CMAKE_CXX_FLAGS_INIT "${_cxx_flags}")
set(CMAKE_ASM_FLAGS_INIT "${_asm_flags}")

set(_link "${ARDUINO_PROP_recipe__c__combine__pattern}")
string(REGEX REPLACE "^\"[^\"]+\"[ \t]+" "" _link "${_link}")
string(REGEX REPLACE "[ \t]+-o[ \t]+.*$" "" _link "${_link}")
string(REGEX REPLACE "[ \t]+" " " _link "${_link}")
string(STRIP "${_link}" _link)
set(CMAKE_EXE_LINKER_FLAGS_INIT "${_link}")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(ARDUINO_CORE_PATH     "${ARDUINO_PROP_build__core__path}"            CACHE PATH "Arduino core source dir"     FORCE)
set(ARDUINO_VARIANT_PATH  "${ARDUINO_PROP_build__variant__path}"         CACHE PATH "Arduino variant source dir"  FORCE)
set(ARDUINO_PLATFORM_PATH "${ARDUINO_PROP_build__board__platform__path}" CACHE PATH "Arduino platform install dir" FORCE)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")
