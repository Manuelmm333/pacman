cmake_minimum_required(VERSION 3.10)
project(PacmanMods)

add_library(InvisibleGhost SHARED InvisibleGhost/InvisibleGhost.cpp)

target_include_directories(InvisibleGhost PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../GameFramework/include
)

target_link_libraries(InvisibleGhost PUBLIC
  SFML::Graphics
)

target_compile_features(InvisibleGhost PRIVATE ${COMMON_COMPILE_FEAUTRES})