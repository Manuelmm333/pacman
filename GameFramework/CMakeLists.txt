add_library(GameFramework STATIC
  src/Entity.cpp
  src/Scene.cpp
  src/GraphicComponent.cpp
  src/TransformComponent.cpp
  src/PhysicsComponent.cpp
  src/PhysicsManager.cpp
  src/ScriptComponent.cpp
  src/MapComponent.cpp
  src/GameManager.cpp
)

target_include_directories(GameFramework PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(GameFramework PUBLIC
  SFML::Graphics
)

target_compile_features(GameFramework PRIVATE ${COMMON_COMPILE_FEAUTRES})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)