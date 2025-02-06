cmake_minimum_required(VERSION 3.14)
project(hsu_ai_torque)

# Cross-compilation settings
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(toolchainpath C:/build/2025Q1/x64/sysroots)
set(CMAKE_C_COMPILER ${toolchainpath}/x86_64-w64-mingw32/usr/bin/x86_64-nilrt-linux/x86_64-nilrt-linux-gcc.exe)
set(CMAKE_CXX_COMPILER ${toolchainpath}/x86_64-w64-mingw32/usr/bin/x86_64-nilrt-linux/x86_64-nilrt-linux-g++.exe)
set(CMAKE_SYSROOT ${toolchainpath}/core2-64-nilrt-linux)

# NI-DAQmx settings
set(NIDAQMX_ROOT "C:/Program Files (x86)/National Instruments/Shared/ExternalCompilerSupport/C") 
set(LIBNIDAQMX_LIBRARY "${NIDAQMX_ROOT}/lib64/gcc/libnidaqmx.so")
find_path(LIBNIDAQMX_INCLUDE_DIR 
    NAMES "NIDAQmx.h"
    PATHS ${NIDAQMX_ROOT}
    PATH_SUFFIXES "include"
)
include_directories(${LIBNIDAQMX_INCLUDE_DIR})

# Debugging output
message("Library: ${LIBNIDAQMX_LIBRARY}")
message("Include: ${LIBNIDAQMX_INCLUDE_DIR}")

# Build settings
set(EXECUTABLE_OUTPUT_PATH bin)
set(CMAKE_BUILD_TYPE Debug)

add_executable(main ../src/main.cpp)
target_link_libraries(main PRIVATE "${LIBNIDAQMX_LIBRARY}")