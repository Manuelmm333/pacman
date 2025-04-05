project(FastGhost)

add_library(FastGhost SHARED
    FastGhost.cpp
    FastGhost.h
)

target_include_directories(FastGhost PUBLIC
    ${CMAKE_SOURCE_DIR}/GameFramework/include
)

target_link_libraries(FastGhost PUBLIC
    GameFramework
)


target_compile_features(FastGhost PRIVATE ${COMMON_COMPILE_FEAUTRES}) 