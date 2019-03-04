#include "Body.h"
#include "Box.h"
#include "Box2D/Box2D.h"

#include <Actor.h>
#include <Log.h>

using namespace Core;

void Box::SetOffset(Vector2 offset)
{
  this->offset = offset;
}

void Box::SetExtent(Vector2 extent)
{
  this->extent = extent;
}

void Box::SetAngle(float angle)
{
  this->angle = angle;
}

void Box::Apply()
{
	Body* body = GetParent()->GetComponent<Body>();

	if (!body)
	{
		PERROR("ERROR_MISSING_BODY");
		throw;
	}

	if (!fixture)
	{
		Box2DPolygonShape shape;
		shape.SetAsBox(extent.x, extent.y, BOX2D(offset), angle);

		Box2DFixtureInfo info;
		info.density = density;
		info.friction = friction;
		info.restitution = restitution;
		info.shape = &shape;

		fixture = body->body->CreateFixture(&info);
	}
	else
	{
		Box2DPolygonShape* shape = (Box2DPolygonShape*)fixture->GetShape();
		shape->SetAsBox(extent.x, extent.y, BOX2D(offset), angle);
	}
}

Type Box::GetType()
{
	return typeid(Box);
}
