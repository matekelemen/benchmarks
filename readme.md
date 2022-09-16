## Requirements
- *CMake*
- *[google benchmark](https://github.com/google/benchmark)*
- *[boost](https://github.com/boostorg/boost)*

## Build
- **Linux** : execute the *[compile](https://www.github.com/matekelemen/benchmarks/blob/master/compile)* bash script.
- **other** : run *CMake* (don't forget to set *CMAKE_BUILD_TYPE* to *Release*). You can set the *RUN_BENCHMARKS* variable to *ON* to execute all built benchmarks automatically after compiling.

## Usage
Binaries are built in the *build* directory, just run the executables. Alternatively, you can pass the following flags to the *[compile](https://www.github.com/matekelemen/benchmarks/blob/master/compile)* script:
- *-r* : run all compiled executables
- *-d* : disable CPU power scaling for all
