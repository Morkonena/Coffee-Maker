#include "Hitbox.h"
#include <Box2D/Box2D.h>

using namespace Core;

void Hitbox::SetDensity(float density)
{
	this->density = density;
}

float Hitbox::GetDensity() const
{
	return density;
}

void Hitbox::SetFriction(float friction)
{
	this->friction = friction;
}

float Hitbox::GetFriction() const
{
	return friction;
}

void Hitbox::SetRestitution(float restitution)
{
	this->restitution = restitution;
}

float Hitbox::GetRestitution() const
{
	return restitution;
}

void Hitbox::OnDestroy()
{
	Box2DBody* body = fixture->GetBody();
	body->DestroyFixture(fixture);
	fixture = nullptr;
}
