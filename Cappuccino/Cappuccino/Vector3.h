//
// Created by Mörkönenä on 9.7.2018
//

#ifndef CORE_VECTOR_III_H
#define CORE_VECTOR_III_H

namespace Core
{
  class Vector2;
  class Vector4;

  class Vector3
  {
  public:
		float x, y, z;

  public:
    Vector3(float scale = 0.0f);

    template<typename X, typename Y, typename Z>
    Vector3(X, Y, Z);

    bool operator==(const Vector3& rhs) const;

    Vector3& operator+=(const Vector3& rhs);
    Vector3& operator-=(const Vector3& rhs);

    template<typename T>
    Vector3& operator*=(T);

    Vector3 operator+(const Vector3& rhs) const;
    Vector3 operator-(const Vector3& rhs) const;

    template<typename T>
    Vector3 operator*(T) const;

    float operator*(const Vector3& rhs) const;

    operator Vector2() const;
    operator Vector4() const;

    float GetMagnitude() const;
    void Normalize();

    static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
    static Vector3 Scale(Vector3 a, Vector3 b);

    static Vector3 AngleAxis(float angle, Vector3 axis);
  };

  inline Vector3::Vector3(float scale)
  {
    this->x = scale;
    this->y = scale;
    this->z = scale;
  }

  template<typename X, typename Y, typename Z>
  inline Vector3::Vector3(X x, Y y, Z z)
  {
    this->x = static_cast<float>(x);
    this->y = static_cast<float>(y);
    this->z = static_cast<float>(z);
  }

  template<typename T>
  inline Vector3& Vector3::operator*=(T scalar)
  {
    this->x *= static_cast<float>(scalar);
    this->y *= static_cast<float>(scalar);
    this->z *= static_cast<float>(scalar);

    return *this;
  }

  template<typename T>
  inline Vector3 Vector3::operator*(T scalar) const
  {
    return (Vector3(*this) *= scalar);
  }
}

#endif // !CORE_VECTOR_III_H


