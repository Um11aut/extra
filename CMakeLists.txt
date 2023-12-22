# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(Extra)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files to the project
set(SOURCES
    main.cpp
)

# Add executable target
add_executable(Extra ${SOURCES})

