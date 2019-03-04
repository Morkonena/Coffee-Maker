#include "Actor.h"
#include "Vector2.h"

#include <algorithm>
#include <cstring>

using namespace Core;

void Actor::AddChild(Actor* actor)
{
  childs.push_back(actor);
}

void Actor::RemoveChild(Actor* actor)
{
  childs.erase(std::find(childs.begin(), childs.end(), actor));
}

void Actor::OnTick()
{
  for (auto& component : components)
  {
    if (component->GetEnabled())
    {
      component->OnTick();
    }
  }

  for (auto child : childs)
  {
    if (child->GetEnabled())
    {
      child->OnTick();
    }
  }
}

void Actor::OnPhysicsTick()
{
  for (auto& component : components)
  {
    if (component->GetEnabled())
    {
      component->OnPhysicsTick();
    }
  }

  for (auto child : childs)
  {
    if (child->GetEnabled())
    {
      child->OnPhysicsTick();
    }
  }
}

void Actor::SetEnabled(bool enabled)
{
  this->enabled = enabled;
}

bool Actor::GetEnabled(bool hierarchy) const
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

void Actor::SetName(String name)
{
  this->name = name;
}

std::string Actor::GetName() const
{
  return name;
}

void Actor::SetParent(Actor* new_parent)
{
  if (parent)
  {
    parent->RemoveChild(this);
  }

  parent = new_parent;

  if (parent)
  {
    parent->AddChild(this);
  }
}

Actor* Actor::GetParent() const
{
  return parent;
}

void Actor::SetWorldPosition(Vector3 position)
{
  if (parent)
  {
    this->position = position - parent->GetWorldPosition();
  }
  else
  {
    this->position = position;
  }
}

void Actor::SetWorldRotation(Vector3 rotation)
{
  if (parent)
  {
    this->rotation = rotation - parent->GetWorldRotation();
  }
  else
  {
    this->rotation = rotation;
  }
}

void Actor::SetWorldScale(Vector3 scale)
{
  if (parent)
  {
    Vector3 parent_scale = parent->GetWorldScale();
    this->scale = Vector3(scale.x / parent_scale.x, scale.y / parent_scale.y, scale.z / parent_scale.z);
  }
  else
  {
    this->scale = scale;
  }
}

Vector3 Actor::GetWorldPosition() const
{
  Vector4 point = static_cast<Vector4>(position);

  if (parent)
  {
    point = parent->GetWorldMatrix() * point;
  }

  return static_cast<Vector3>(point);
}

Vector3 Actor::GetWorldRotation() const
{
  if (parent)
  {
    return parent->GetWorldRotation() + rotation;
  }
  else
  {
    return rotation;
  }
}

Vector3 Actor::GetWorldScale() const
{
  if (parent)
  {
    Vector3 scale = parent->GetWorldScale();
    return Vector3(scale.x * this->scale.x, scale.y * this->scale.y, scale.z * this->scale.z);
  }
  else
  {
    return scale;
  }
}

Matrix Actor::GetWorldMatrix() const
{
  if (parent)
  {
    return parent->GetWorldMatrix() * GetMatrix();
  }
  else
  {
    return GetMatrix();
  }
}

Matrix Actor::GetMatrix() const
{
  return Matrix::Translate(position) * Matrix::Rotate(rotation) * Matrix::Scale(scale);
}

Actor* Actor::FindChild(std::string name) const
{
  for (Actor* child : childs)
  {
    if (child->name.compare(name) == 0)
    {
      return child;
    }
  }

  return nullptr;
}

Actor* Actor::GetChildAt(int i)
{
  return childs[i];
}

Actor** Actor::GetChilds()
{
  return childs.data();
}

int Actor::GetChildCount() const
{
  return (int)childs.size();
}

Component* Actor::GetComponentAt(int i)
{
  return components[i].get();
}

int Actor::GetComponentCount() const
{
  return (int)components.size();
}

void Actor::Destroy()
{
	for (auto child : childs)
	{
		child->Destroy();
	}

	delete this;
}
