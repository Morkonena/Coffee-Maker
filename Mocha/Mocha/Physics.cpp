#include "Body.h"
#include "Box2D/Box2D.h"

#include <Actor.h>
#include <Log.h>
#include <Standard.h>
#include <Vector2.h>

using namespace Core;

Managed<Box2DWorld> Physics::World;
List<Body*> Physics::Bodies;

int Physics::Quality::Movement;
int Physics::Quality::Position;

void Physics::Initialize(Vector2 gravity)
{
  Quality::Movement = 3;
  Quality::Position = 3;

	World = std::make_unique<Box2DWorld>(BOX2D(gravity));

  SUCCESS("Physics: OK");
}

void Physics::SetGravity(Vector2 gravity)
{
  World->SetGravity(BOX2D(gravity));
}

typedef b2RayCastCallback Box2DRaycastCallback;

Body* Physics::Pointcast(Vector2 x)
{
	Box2DVector& point = BOX2D(x);
  Box2DBody* bodies = World->GetBodyList();

  for (Box2DBody* body = bodies; body != nullptr; body = body->GetNext())
  {
    Box2DFixture* fixtures = body->GetFixtureList();

    for (Box2DFixture* fixture = fixtures; fixture != nullptr; fixture = fixture->GetNext())
    {
      if (fixture->TestPoint(point))
      {
        return (Body*)body->GetUserData();
      }
    }
  }

  return nullptr;
}

void Physics::Raycast(Vector2 a, Vector2 b, Function<RaycastCommand(Hit&)>& callback)
{
  class Callback : public Box2DRaycastCallback
  {
  public:
    Function<RaycastCommand(Hit&)> callback;

    Callback(Function<RaycastCommand(Hit&)>& callback) : callback(callback)
    {}

    virtual float32 ReportFixture(Box2DFixture* fixture, const Box2DVector& point, const Box2DVector& normal, float fraction) override
    {
      Hit hit;
      hit.body   = static_cast<Body*>(fixture->GetBody()->GetUserData());
			hit.normal = CONST_CAPPUCCINO(normal);
			hit.point  = CONST_CAPPUCCINO(point);

      return static_cast<float>(callback(hit));
    }
  };

  World->RayCast(new Callback(callback), BOX2D(a), BOX2D(b));
}

Box2DBody* Physics::CreateBody(Body* body)
{
  Vector2 position = body->GetParent()->GetWorldPosition();

  Box2DBodyInfo info;
	info.position = BOX2D(position);
	info.angle	= body->GetParent()->GetWorldRotation().z;

  Box2DBody* handle = World->CreateBody(&info);

  if (!handle)
  {
    PERROR("ERROR_CREATE_BODY");
    throw;
  }

  Bodies.push_back(body);

  return handle;
}

void Physics::RemoveBody(Body* body, Box2DBody* handle)
{
  World->DestroyBody(handle);
  Bodies.erase(std::find(Bodies.begin(), Bodies.end(), body));
}

void Physics::Tick(float delta)
{
  // 1. Update all bodies to match their actors
  for (Body* body : Bodies)
  {
    body->SetPosition(body->GetParent()->GetWorldPosition());
  }

  // 2. Process physics
  World->Step(delta, Quality::Movement, Quality::Position);

  // 3. Update all physics actors to match their bodies
  for (Body* body : Bodies)
  {
    Actor* parent = body->GetParent();
    parent->SetWorldPosition(body->GetPosition());
    parent->SetWorldRotation(Vector3(0, 0, body->GetAngle()));
  }
}
