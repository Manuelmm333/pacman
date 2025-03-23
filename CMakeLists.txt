cmake_minimum_required(VERSION 3.10.0)
project(Pacman VERSION 0.1.0 LANGUAGES C CXX)

# Forzar a que los ejecutables se guarden en build/Debug o build/Release
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)

add_executable(Pacman main.cpp)
