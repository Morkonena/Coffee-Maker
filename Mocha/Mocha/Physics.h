//
// Created by M�rk�nen� on 8.9.2018
//

#ifndef CORE_PHYSICS_H
#define CORE_PHYSICS_H

#include <Standard.h>
#include <Vector2.h>

typedef struct	b2Vec2					Box2DVector;

typedef class		b2Shape					Box2DShape;
typedef class		b2PolygonShape	Box2DPolygonShape;
typedef class		b2CircleShape		Box2DCircleShape;

typedef struct	b2FixtureDef		Box2DFixtureInfo;
typedef struct	b2BodyDef				Box2DBodyInfo;
typedef class		b2Body					Box2DBody;
typedef class		b2Fixture				Box2DFixture;

typedef class		b2World					Box2DWorld;

#define BOX2D(X) *reinterpret_cast<Box2DVector*>(&(X))
#define CONST_BOX2D(X) *reinterpret_cast<const Box2DVector*>(&(X))
#define CAPPUCCINO(X) *reinterpret_cast<Vector2*>(&(X))
#define CONST_CAPPUCCINO(X) *reinterpret_cast<const Vector2*>(&(X))

namespace Core
{
  class Body;

	enum RaycastCommand : int
	{
		RAYCAST_COMMAND_STOP = 0,
		RAYCAST_COMMAND_CONTINUE = -1
	};

  struct PhysicsBodyUpdate
  {
    Vector2 Position;
    float Rotation;
  };

  class PhysicsUpdate
  {
  private:
    Map<Body*,PhysicsBodyUpdate> Updates;

  private:
    int Priority;

  public:
    PhysicsUpdate (int priority);

    void Merge (PhysicsUpdate& update);

    int GetPriority() const;
  };

  struct PhysicsThread
  {
    List<PhysicsUpdate> Updates;
    int Priority;
  };

	class PhysicsBridge
	{
  private:
    static List<PhysicsUpdate> Updates;
    static Map<int, PhysicsThread> Threads;
    static Lock UpdateLock;

  public:
    static void Initialize (int priority);
    static void Push (PhysicsUpdate& update);

  public:
    static PhysicsUpdate GetMergedUpdate();
	};

  class Physics
  {
	private:
		static Managed<Box2DWorld> World;
		static List<Body*> Bodies;

	public:
    class Quality
    {
		public:
      static int Movement;
      static int Position;
		};

    static void Initialize (Vector2 gravity);
    static void SetGravity (Vector2 gravity);

    struct Hit
    {
      Body* body;

      Vector2 point;
      Vector2 normal;
    };

    static Body*	Pointcast	(Vector2 point);
		static void		Raycast		(Vector2 start, Vector2 end, Function<RaycastCommand(Hit& hit)>& callback);

		static Box2DBody*		CreateBody (Body* body);
		static void					RemoveBody (Body* body, Box2DBody* handle);

		static void Tick (float delta);
	};
}

#endif // !CORE_PHYSICS_H
