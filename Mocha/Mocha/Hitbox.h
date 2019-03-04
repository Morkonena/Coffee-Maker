//
// Created by Mörkönenä on 8.9.2018
//

#ifndef CORE_HITBOX_H
#define CORE_HITBOX_H

#include <Component.h>
#include "Physics.h"

namespace Core
{
  class Hitbox : public Component
  {
  protected:
    mutable Box2DFixture* fixture = nullptr;

		float density;
		float friction;
		float restitution;
			
  public:
		using Component::Component;

    void	SetDensity (float density);
    float GetDensity () const;

    void	SetFriction (float friction);
    float GetFriction () const;

    void	SetRestitution (float restitution);
    float GetRestitution () const;

		virtual void Apply() = 0;
		virtual void OnDestroy() override;
  };
}

#endif // !CORE_HITBOX_H