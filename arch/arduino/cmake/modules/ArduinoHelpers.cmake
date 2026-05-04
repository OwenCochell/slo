# ArduinoHelpers — convenience functions for Arduino targets.
#
#   arduino_executable(<name> SOURCES <files...> [LIBRARIES <libs...>])
#       Adds an executable producing <name>.elf, <name>.hex, and prints size.
#       Automatically links ArduinoCore::Core and libm.
#
#   arduino_upload(<name> [PORT <port>])
#       Adds a custom target <name>_upload that flashes via arduino-cli.
#       Port can also be supplied at build time via -DPORT=...

include_guard(GLOBAL)

if(NOT TARGET ArduinoCore::Core)
  include(ArduinoCore)
endif()

function(arduino_executable name)
  cmake_parse_arguments(ARG "" "" "SOURCES;LIBRARIES" ${ARGN})
  if(NOT ARG_SOURCES)
    message(FATAL_ERROR "arduino_executable(${name}): SOURCES required")
  endif()

  add_executable(${name} ${ARG_SOURCES})
  set_target_properties(${name} PROPERTIES SUFFIX ".elf")
  target_link_libraries(${name} PRIVATE ArduinoCore::Core m ${ARG_LIBRARIES})

  set(_elf "$<TARGET_FILE:${name}>")
  set(_hex "${CMAKE_CURRENT_BINARY_DIR}/${name}.hex")
  set(_eep "${CMAKE_CURRENT_BINARY_DIR}/${name}.eep")

  add_custom_command(TARGET ${name} POST_BUILD
    COMMAND "${CMAKE_OBJCOPY}" -O ihex -R .eeprom "${_elf}" "${_hex}"
    COMMAND "${CMAKE_OBJCOPY}" -O ihex -j .eeprom
            --set-section-flags=.eeprom=alloc,load --no-change-warnings
            --change-section-lma .eeprom=0 "${_elf}" "${_eep}"
    BYPRODUCTS "${_hex}" "${_eep}"
    COMMENT "Generating ${name}.hex / ${name}.eep"
    VERBATIM
  )

  if(CMAKE_SIZE_UTIL)
    add_custom_command(TARGET ${name} POST_BUILD
      COMMAND "${CMAKE_SIZE_UTIL}" -A "${_elf}"
      COMMENT "Size of ${name}.elf"
      VERBATIM
    )
  endif()

  set_target_properties(${name} PROPERTIES ARDUINO_HEX_FILE "${_hex}")
endfunction()

function(arduino_upload name)
  cmake_parse_arguments(ARG "" "PORT" "" ${ARGN})
  if(NOT TARGET ${name})
    message(FATAL_ERROR "arduino_upload(${name}): no such target")
  endif()
  if(NOT ARDUINO_CLI)
    message(FATAL_ERROR "arduino_upload: ARDUINO_CLI not set (toolchain not loaded?)")
  endif()
  if(ARG_PORT)
    set(_port "${ARG_PORT}")
  else()
    set(_port "$<IF:$<BOOL:$ENV{PORT}>,$ENV{PORT},/dev/ttyACM0>")
  endif()

  add_custom_target(${name}_upload
    COMMAND "${ARDUINO_CLI}" upload
            --fqbn "${ARDUINO_FQBN}"
            --port "${_port}"
            --input-dir "$<TARGET_FILE_DIR:${name}>"
    DEPENDS ${name}
    COMMENT "Uploading ${name} via arduino-cli to ${_port}"
    VERBATIM
  )
endfunction()
