//
// Created by Mörkönenä on 25.12.2018
//

#ifndef CORE_CIRCLE_H
#define CORE_CIRCLE_H

#include <Vector2.h>
#include "Hitbox.h"

namespace Core
{
	class Circle : public Hitbox
	{
	private:
		Vector2 offset;
		float radius;

	public:
		using Hitbox::Hitbox;

		void SetOffset (Vector2 offset);
		void SetRadius (float radius);

		virtual void Apply() override;
		virtual Type GetType() override;
	};
}

#endif // !CORE_CIRCLE_H