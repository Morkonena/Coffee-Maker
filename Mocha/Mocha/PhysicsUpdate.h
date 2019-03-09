//
// Created by Mörkönenä 6.3.2019
//

#ifndef CORE_PHYSICS_UPDATE
#define CORE_PHYSICS_UPDATE

namespace Core
{
  class PhysicsUpdate
  {
  private:
    Map<Body*, PhysicsBodyUpdate> Updates;
  private:
    friend class PhysicsBridge;
    int Priority;
  public:
    PhysicsUpdate Merge (PhysicsUpdate& with);

    PhysicsUpdate& GetUpdate(Body* body) const;
    int GetPriority() const;
  };
}

#endif // !CORE_PHYSICS_UPDATE
