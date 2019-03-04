//
// Created by Mörkönenä on 8.9.2018
//

#ifndef CORE_BOX_H
#define CORE_BOX_H

#include <Vector2.h>
#include "Hitbox.h"

namespace Core
{
  class Box : public Hitbox
  {
  private:
    Vector2 offset;
    Vector2 extent;

    float angle;
    
  public:
		using Hitbox::Hitbox;

    void SetOffset (Vector2 offset);
    void SetExtent (Vector2 extent);
    void SetAngle  (float angle);

		virtual void Apply() override;
		virtual Type GetType() override;
  };
}

#endif // !CORE_BOX_H