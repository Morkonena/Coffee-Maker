#include "Body.h"
#include "Box.h"
#include "Box2D/Box2D.h"

#include <Actor.h>
#include <Log.h>
#include <Standard.h>

using namespace Core;

Body::Body(Actor* parent) : Component(parent)
{
  Actor* x = parent->GetParent();

  // Physics body as a child to another body isn't supported
  while (x)
  {
    if (x->HasComponent<Body>())
    {
      PERROR("ERROR_NOT_ALLOWED");
      throw;
    }

    x = x->GetParent();
  }

  body = Physics::CreateBody(this);
  body->SetUserData(this);
}

void Body::SetEnabled(bool enabled)
{
  Component::SetEnabled(enabled);
  body->SetActive(enabled);
}

void Body::SetVelocity(Vector2 velocity)
{
  body->SetLinearVelocity(BOX2D(velocity));
}

Vector2 Body::GetVelocity() const
{
  return CONST_CAPPUCCINO(body->GetLinearVelocity());
}

void Body::SetAngularVelocity(float velocity)
{
  body->SetAngularVelocity(velocity);
}

float Body::GetAngularVelocity() const
{
  return body->GetAngularVelocity();
}

void Body::SetPosition(Vector2 position)
{
  body->SetTransform(BOX2D(position), GetParent()->GetWorldRotation().z);
}

void Body::SetAngle(float angle)
{
	Vector3 position = GetParent()->GetWorldPosition();
  body->SetTransform(BOX2D(position), angle);
}

Vector2 Body::GetPosition() const
{
  const Box2DVector& position = body->GetPosition();
  return CONST_CAPPUCCINO(position);
}

float Core::Body::GetAngle() const
{
  return body->GetAngle();
}

void Body::SetMovementType(MovementType type)
{
  switch (type)
  {
  case MOVEMENT_TYPE_STATIC:
    body->SetType(b2_staticBody);
    break;
  case MOVEMENT_TYPE_DYNAMIC:
    body->SetType(b2_dynamicBody);
    break;
  case MOVEMENT_TYPE_KINEMATIC:
    body->SetType(b2_kinematicBody);
    break;
  }
}

Type Body::GetType()
{
  return typeid(Body);
}

void Body::OnDestroy()
{
	Physics::RemoveBody(this, body);
}
