//
// Created by Mörkönenä on 9.7.2018
//

#ifndef CORE_ACTOR_H
#define CORE_ACTOR_H

#include "Component.h"
#include "Matrix.h"
#include "Standard.h"
#include "Vector3.h"

namespace Core
{
  class Actor
  {
  private:
    String name;
    Actor* parent;

    List<Managed<Component>> components;
		List<Actor*> childs;

		bool enabled = true;

	private:
    void AddChild     (Actor* actor);
    void RemoveChild  (Actor* actor);

	public:
		Vector3 position;
		Vector3 rotation;
		Vector3 scale = Vector3(1, 1, 1);

  public:
    void OnTick         ();
    void OnPhysicsTick  ();

    void SetEnabled (bool enabled);
    bool GetEnabled (bool hierarchy = false) const;

    void    SetName (String name);
    String	GetName () const;

    void    SetParent (Actor* parent);
    Actor*  GetParent () const;

    void SetWorldPosition (Vector3 position);
    void SetWorldRotation (Vector3 angle);
    void SetWorldScale    (Vector3 scale);

    Vector3 GetWorldPosition  () const;
    Vector3 GetWorldRotation  () const;
    Vector3 GetWorldScale     () const;

    Matrix GetWorldMatrix () const;
    Matrix GetMatrix      () const;

    Actor* FindChild(std::string name) const;

    Actor*  GetChildAt  (int i);
    Actor** GetChilds   ();

    int GetChildCount() const;

    template<class T>
    T* AddComponent();

    template<class T>
    T* GetComponent();

    template<class T>
    bool HasComponent();

    Component* GetComponentAt(int i);

    template<class T>
    List<Component*> GetComponents() const;

    int GetComponentCount() const;

		void Destroy();
  };

  template<class T>
  inline T* Actor::AddComponent()
  {
    auto component = std::make_unique<T>(this);
    auto address = static_cast<T*>(component.get());

    components.push_back(std::move(component));

    return address;
  }

  template<class T>
  inline bool Actor::HasComponent()
  {
    for (auto& component : components)
    {
      if (component->GetType() == typeid(T))
      {
        return true;
      }
    }

    return false;
  }

  template<class T>
  inline T* Actor::GetComponent()
  {
    for (auto& component : components)
    {
      if (component->GetType() == typeid(T))
      {
        return static_cast<T*>(component.get());
      }
    }

    return nullptr;
  }

  template<class T>
  inline List<Component*> Actor::GetComponents() const
  {
    List<Component*> components;

    for (auto& component : this->components)
    {
      if (component->GetType() == typeid(T))
      {
        components.push_back(component.get());
      }
    }

    return components;
  }
}

#endif // !CORE_ACTOR_H