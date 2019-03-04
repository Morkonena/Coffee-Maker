#include "Player.h"
#include <cmath>

#define WALKING_SPEED 100.0f
#define PI 3.14159265f

void Player::OnTick()
{
	Body* body = GetParent()->GetComponent<Body>();

	Vector2 middle = Vector2(1920, 1080) * 0.5f;
	Vector2 delta = Input::GetCursorPosition() - middle;
	delta.Normalize();

	Vector2 velocity = delta * WALKING_SPEED;

	if (!Input::IsCursorPressed())
	{
		velocity = Vector2();
	}

	velocity = Vector2(1.0f, 0.0f) * WALKING_SPEED;

	velocity.y = -velocity.y;


	body->SetVelocity(velocity);

	Camera::position = Vector3::Lerp(Camera::position, GetParent()->position, 0.016f * 3);
}

Type Player::GetType()
{
	return typeid(Player);
}
