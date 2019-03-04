//
// Created by Mörkönenä on 8.9.2018
//

#ifndef CORE_BODY_H
#define CORE_BODY_H

#include "Box.h"
#include "Circle.h"

#include "Physics.h"

namespace Core
{
  enum MovementType
  {
    MOVEMENT_TYPE_STATIC,
    MOVEMENT_TYPE_DYNAMIC,
    MOVEMENT_TYPE_KINEMATIC
  };

  class Body : public Component
  {
  private:
    friend class Box;
    friend class Circle;

    Box2DBody* body;

  public:
    Body(Actor* parent);

    void			SetVelocity (Vector2 velocity);
    Vector2		GetVelocity () const;

    void		SetAngularVelocity (float velocity);
    float		GetAngularVelocity () const;

    void			SetPosition (Vector2 position);
		Vector2		GetPosition () const;

    void		SetAngle (float angle);
    float		GetAngle () const;

    void SetMovementType (MovementType type);

		virtual void SetEnabled(bool enabled) override;
    virtual Type GetType() override;

		virtual void OnDestroy() override;
  };
}

#endif // !CORE_BODY_H