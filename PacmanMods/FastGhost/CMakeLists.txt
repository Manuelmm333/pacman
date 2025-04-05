add_library(FastGhost SHARED
    FastGhost.cpp
    FastGhost.h
)

target_include_directories(FastGhost PRIVATE
    ${CMAKE_SOURCE_DIR}/GameFramework/include
)

target_link_libraries(FastGhost PRIVATE
    GameFramework
)

set_target_properties(FastGhost PROPERTIES
    PREFIX ""
    OUTPUT_NAME "FastGhost"
)

target_compile_features(FastGhost PRIVATE ${COMMON_COMPILE_FEAUTRES}) 