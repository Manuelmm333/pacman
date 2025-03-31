#include "ScriptComponent.h"
#include "Entity.h"


void ScriptComponent::update(const Entity* parent/*DeltaTime*/)
{
  if (m_scriptFunction)
  {
    m_scriptFunction(parent);
  }
}