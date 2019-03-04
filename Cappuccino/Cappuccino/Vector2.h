//
// Created by Mörkönenä on 10.7.2018
//

#ifndef CORE_VECTOR_II_H
#define CORE_VECTOR_II_H

namespace Core
{
  class Vector3;
  class Vector4;

  class Vector2
  {
  public:
    float x, y;

  public:
    Vector2(float scale = 0.0f);

    template<typename X, typename Y>
    Vector2(X, Y);

    bool operator==(const Vector2& rhs) const;

    Vector2& operator+=(const Vector2& rhs);
    Vector2& operator-=(const Vector2& rhs);
    
    template<typename T>
    Vector2& operator*=(T);

    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;

    template<typename T>
    Vector2 operator*(T) const;

    float operator*(const Vector2& rhs) const;

    operator Vector3() const;
    operator Vector4() const;

    float GetMagnitude() const;
    void Normalize();

    static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
  };

  inline Vector2::Vector2(float scale)
  {
    x = scale;
    y = scale;
  }

  template<typename X, typename Y>
  inline Vector2::Vector2(X x, Y y)
  {
    this->x = static_cast<float>(x);
    this->y = static_cast<float>(y);
  }

  template<typename T>
  inline Vector2& Vector2::operator*=(T scalar)
  {
    x *= static_cast<float>(scalar);
    y *= static_cast<float>(scalar);

    return *this;
  }

  template<typename T>
  inline Vector2 Vector2::operator*(T scalar) const
  {
    return Vector2(x * static_cast<float>(scalar), y * static_cast<float>(scalar));
  }
}

#endif // !CORE_VECTOR_II_H