//
// Created by Mörkönenä on 11.7.2018
//

#ifndef CORE_COMPONENT_H
#define CORE_COMPONENT_H

#include <typeinfo>
typedef const std::type_info& Type;

namespace Core
{
  class Actor;

  class Component
  {
  private:
    Actor* parent;
    bool enabled = true;

  public:
    Component(Actor* parent);
    Component(const Component& component) = default;
    Component& operator=(const Component& component) = default;
    Component(Component&& component) = default;
    Component& operator=(Component&& component) = default;

    virtual ~Component();

    Actor* GetParent() const;

    virtual void SetEnabled(bool enabled);
    virtual bool GetEnabled(bool hierarchy = false) const;

    virtual void OnTick() {}
    virtual void OnPhysicsTick() {}

    virtual void OnToggle(bool on) {}
    virtual void OnDestroy() {}

    virtual Type GetType() = 0;
  };
}

#endif // !CORE_COMPONENT_H