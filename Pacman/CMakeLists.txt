cmake_minimum_required(VERSION 3.10)

# Define the executable
add_executable(Pacman main.cpp)

# Include directories
target_include_directories(Pacman PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../GameFramework/include
)

# Link libraries if needed
target_link_libraries(Pacman PRIVATE
  GameFramework
)

target_compile_features(Pacman PRIVATE ${COMMON_COMPILE_FEAUTRES})

add_custom_command(
    TARGET Pacman POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/../Assets
        $<TARGET_FILE_DIR:Pacman>/Assets
    COMMENT "Copiando assets para Pacman"
)