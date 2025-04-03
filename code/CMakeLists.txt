cmake_minimum_required(VERSION 3.10)
project(GameBoyEmulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source files
set(SOURCES
    cppFiles/bus.cpp
    cppFiles/cart.cpp
    cppFiles/cpu.cpp
    cppFiles/emu.cpp
    cppFiles/instruction.cpp
    main.cpp
)

# Set header files
set(HEADERS
    headers/bus.h
    headers/cart.h
    headers/cpu.h
    headers/emu.h
    headers/instruction.h
    headers/st_ty.h
    headers/logger.h
)

# Include headers directory
include_directories(headers)

# Create executable
add_executable(GameBoyEmulator ${SOURCES} ${HEADERS})
