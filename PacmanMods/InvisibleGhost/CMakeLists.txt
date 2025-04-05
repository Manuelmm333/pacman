project(InvisibleGhost)

add_library(InvisibleGhost SHARED InvisibleGhost.cpp)

target_include_directories(InvisibleGhost PUBLIC 
  ${CMAKE_SOURCE_DIR}/GameFramework/include
)

target_link_libraries(InvisibleGhost PUBLIC
  GameFramework
)

target_compile_definitions(InvisibleGhost PRIVATE 
    INVISIBLE_GHOST_EXPORTS
)
