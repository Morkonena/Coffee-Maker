#include "Component.h"
#include "Actor.h"

using namespace Core;

Component::Component(Actor* parent)
{
  this->parent = parent;
}

Component::~Component()
{
  OnDestroy();
}

Actor* Component::GetParent() const
{
  return parent;
}

void Component::SetEnabled(bool enabled)
{
  this->enabled = enabled;
}

bool Component::GetEnabled(bool hierarchy) const
{
  if (hierarchy && parent != nullptr)
  {
    return parent->GetEnabled(true);
  }
  else
  {
    return enabled;
  }  
}
