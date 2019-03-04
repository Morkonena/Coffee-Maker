#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include <cmath>

using namespace Core;

bool Vector4::operator==(const Vector4 & rhs) const
{
  return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
}

Vector4& Vector4::operator+=(const Vector4& rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  w += rhs.w;

  return *this;
}

Vector4& Vector4::operator-=(const Vector4& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
  w -= rhs.w;

  return *this;
}

Vector4 Vector4::operator+(const Vector4& rhs) const
{
  return (Vector4(*this) += rhs);
}

Vector4 Vector4::operator-(const Vector4& rhs) const
{
  return (Vector4(*this) -= rhs);
}

float Vector4::operator*(const Vector4& rhs) const
{
  return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}

Vector4::operator Vector2() const
{
  return Vector2(x, y);
}

Vector4::operator Vector3() const
{
  return Vector3(x, y, z);
}

float Vector4::GetMagnitude() const
{
  return sqrtf(x * x + y * y + z * z + w * w);
}

void Vector4::Normalize()
{
  float magnitude = GetMagnitude();

  if (magnitude > 0)
  {
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
    w /= magnitude;
  }
  else
  {
    x = 0;
    y = 0;
    z = 0;
    w = 0;
  }
}

Vector4 Vector4::Lerp(const Vector4& a, const Vector4& b, float t)
{
  return a + (b - a) * t;
}
