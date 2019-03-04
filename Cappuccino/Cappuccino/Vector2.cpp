#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include <cmath>

using namespace Core;

bool Vector2::operator==(const Vector2& rhs) const
{
  return (x == rhs.x) && (y == rhs.y);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
  x += rhs.x;
  y += rhs.y;

  return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
  x -= rhs.x;
  y -= rhs.y;

  return *this;
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
  return (Vector2(*this) += rhs);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
  return (Vector2(*this) -= rhs);
}

float Vector2::operator*(const Vector2& rhs) const
{
  return x * rhs.x + y * rhs.y;
}

Vector2::operator Vector3() const
{
  return Vector3(x, y, 0);
}

Vector2::operator Vector4() const
{
  return Vector4(x, y, 0, 0);
}

float Vector2::GetMagnitude() const
{
  return sqrtf(x * x + y * y);
}

void Vector2::Normalize()
{
  float magnitude = GetMagnitude();

  if (magnitude > 0)
  {
    x /= magnitude;
    y /= magnitude;
  }
  else
  {
    x = 0;
    y = 0;
  }
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
{
  return a + (b - a) * t;
}