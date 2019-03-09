#include "PhysicsUpdate.h"
using namespace Core;

PhysicsUpdate::PhysicsUpdate (int priority) : Priority(priority) {}

PhysicsUpdate PhysicsUpdate::Merge (PhysicsUpdate& with)
{
  PhysicsUpdate merged(Priority);

  // Determine which of these two updates has higher and lower priority
  PhysicsUpdate& higher = (Priority > with.Priority) ? *this : with;
  PhysicsUpdate& lower = (Priority > with.Priority) ? with : *this;

  // Add higher priority body updates first
  merged.Updates.insert(higher.Updates.begin(), higher.Updates.end());

  // Add lower priority body updates next and resolve possible conflicts
  for (auto& update : lower.Updates)
  {
    // Lower priority updates are only added if higher priority update doesn't exist
    if (merged.find(update.first) == merged.end())
    {
      merged.insert(update);
    }
  }

  return merged;
}

PhysicsBodyUpdate& PhysicsUpdate::GetUpdate (Body* body) const
{
  return Updates[body];
}

int PhysicsUpdate::GetPriority() const
{
  return Priority;
}
