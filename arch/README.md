# Architecture Definitions

Each platform SLO runs on MUST have a respective architecture definition!
These definitions define certain functions and types that the SLO standard
library requires to operate.
Architectures are chosen at configure time, and are automatically
included and linked when built.

You should checkout the `example` architecture to see how platforms should be implemented.
Each architecture should implement the required components in a platform specific way.
