#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include <cmath>

using namespace Core;

bool Vector3::operator==(const Vector3& rhs) const
{
  return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;

  return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;

  return *this;
}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
  return (Vector3(*this) += rhs);
}

Vector3 Vector3::operator-(const Vector3& rhs) const
{
  return (Vector3(*this) -= rhs);
}

float Vector3::operator*(const Vector3& rhs) const
{
  return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector3::operator Vector2() const
{
  return Vector2(x, y);
}

Vector3::operator Vector4() const
{
  return Vector4(x, y, z, 1);
}

float Vector3::GetMagnitude() const
{
  return sqrtf(x * x + y * y + z * z);
}

void Vector3::Normalize()
{
  float magnitude = GetMagnitude();

  if (magnitude > 0)
  {
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
  }
  else
  {
    x = 0;
    y = 0;
    z = 0;
  }
}

Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
{
  return a + (b - a) * t;
}

Vector3 Vector3::Scale(Vector3 a, Vector3 b)
{
  return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3 Vector3::AngleAxis(float angle, Vector3 axis)
{
  return Vector3(cosf(angle) * axis.z, cosf(angle) * axis.y, cosf(angle) * axis.x);
}
