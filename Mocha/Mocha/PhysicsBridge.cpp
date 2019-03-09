#include "PhysicsBridge.h"
using namespace Core;

void PhysicsBridge::Initialize(int priority)
{
  int id = std::this_thread::get_id();

  if (Threads.find(id) == Threads.end())
  {
    PhysicsThreadInfo info = {};
    info.Priority = priority;

    Threads.insert(id, info);
  }
  else
  {
    PhysicsThreadInfo& info = Threads[id];
    info.Priority = priority;
  }
}

void PhysicsBridge::Push (PhysicsUpdate& update)
{
  
}
