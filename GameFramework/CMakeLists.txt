add_library(GameFramework STATIC
  src/Entity.cpp
  src/Scene.cpp
  src/GraphicComponent.cpp
  src/TransformComponent.cpp
)

target_include_directories(GameFramework PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(GameFramework PUBLIC
  SFML::Graphics
)

target_compile_features(GameFramework PRIVATE ${COMMON_COMPILE_FEAUTRES})