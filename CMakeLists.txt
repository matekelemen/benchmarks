cmake_minimum_required(VERSION 3.12.0)
project(benchmarks CXX)
set(CMAKE_CXX_STANDARD 17)

set(RUN_BENCHMARKS OFF CACHE BOOL "Execute all compiled benchmarks after compiling.")

find_package(benchmark REQUIRED)
find_package(Boost REQUIRED)
include_directories(include)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${benchmark_INCLUDE_DIRS})

file(GLOB drivers src/*.cpp)
foreach(driver ${drivers})
    get_filename_component(driver_name "${driver}" NAME_WE)
    message(${driver_name})
    add_executable(${driver_name} "${driver}")
    target_link_libraries(${driver_name} PRIVATE benchmark::benchmark)
    target_link_libraries(${driver_name} PRIVATE ${Boost_LIBRARIES})

    if(${RUN_BENCHMARKS})
        add_custom_command(TARGET ${driver_name} POST_BUILD
                           COMMAND "${driver_name}"
                           WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
                           COMMENT "Running benchmark: ${driver_name}")
    endif()
endforeach()
