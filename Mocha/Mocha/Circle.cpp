#include "Body.h"
#include "Circle.h"
#include "Box2D/Box2D.h"

#include <Actor.h>
#include <Log.h>

using namespace Core;

void Circle::SetOffset(Vector2 offset)
{
	this->offset = offset;
}

void Circle::SetRadius(float radius)
{
	this->radius = radius;
}

void Circle::Apply()
{
	Body* body = GetParent()->GetComponent<Body>();

	if (!body)
	{
		PERROR("ERROR_MISSING_BODY");
		throw;
	}

	if (!fixture)
	{
		Box2DCircleShape shape;
		shape.m_p = BOX2D(offset);
		shape.m_radius = radius;

		Box2DFixtureInfo info;
		info.density = density;
		info.friction = friction;
		info.restitution = restitution;
		info.shape = &shape;

		fixture = body->body->CreateFixture(&info);
	}
	else
	{
		Box2DCircleShape* shape = (Box2DCircleShape*)fixture->GetShape();
		shape->m_p = BOX2D(offset);
		shape->m_radius = radius;
	}
}

Type Circle::GetType()
{
	return typeid(Circle);
}
