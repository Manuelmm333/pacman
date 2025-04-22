cmake_minimum_required(VERSION 3.15)
project(SFML_Base)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # .exe files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # .lib and .a files
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # .dll and .so files
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0  # Rama principal de desarrollo
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

set(COMMON_COMPILE_FEAUTRES cxx_std_17)

# Add subdirectories for executable and libraries
add_subdirectory(Pacman)
add_subdirectory(GameFramework)

# Habilitar la generación de DLLs en Windows
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)  # Exporta símbolos automáticamente
endif()