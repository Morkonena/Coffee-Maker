//
// Created by Mörkönenä on 14.7.2018
//

#ifndef CORE_VECTOR_IV_H
#define CORE_VECTOR_IV_H

namespace Core
{
  class Vector2;
  class Vector3;

  class Vector4
  {
  public:
    float x, y, z, w;

  public:
    Vector4(float scale = 0.0f);

    template<typename X, typename Y, typename Z, typename W>
    Vector4(X, Y, Z, W);

    bool operator==(const Vector4& rhs) const;

    Vector4& operator+=(const Vector4& rhs);
    Vector4& operator-=(const Vector4& rhs);

    template<typename T>
    Vector4& operator*=(T);

    Vector4 operator+(const Vector4& rhs) const;
    Vector4 operator-(const Vector4& rhs) const;

    template<typename T>
    Vector4 operator*(T) const;

    float operator*(const Vector4& rhs) const;

    operator Vector2() const;
    operator Vector3() const;

    float GetMagnitude() const;
    void Normalize();

    static Vector4 Lerp(const Vector4& a, const Vector4& b, float t);
  };

  inline Vector4::Vector4(float scale)
  {
    this->x = scale;
    this->y = scale;
    this->z = scale;
    this->w = scale;
  }

  template<typename X, typename Y, typename Z, typename W>
  inline Vector4::Vector4(X x, Y y, Z z, W w)
  {
    this->x = static_cast<float>(x);
    this->y = static_cast<float>(y);
    this->z = static_cast<float>(z);
    this->w = static_cast<float>(w);
  }

  template<typename T>
  inline Vector4& Vector4::operator*=(T scalar)
  {
    this->x *= static_cast<float>(scalar);
    this->y *= static_cast<float>(scalar);
    this->z *= static_cast<float>(scalar);
    this->w *= static_cast<float>(scalar);

    return *this;
  }

  template<typename T>
  inline Vector4 Vector4::operator*(T scalar) const
  {
    return (Vector4(*this) *= scalar);
  }
}

#endif // !CORE_VECTOR_IV_H