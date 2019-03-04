//
// Created by Mörkönenä on 11.7.2018
//

#ifndef CORE_MATRIX_H
#define CORE_MATRIX_H

#include "Vector3.h"
#include "Vector4.h"

namespace Core
{
  class Matrix
  {
  private:
    Vector4 rows[4];

  public:
    Matrix();
    Matrix(const float* data);

    static Matrix GetIdentity(float i = 1.0f);

    static Matrix Translate(const Vector3& translation);
    static Matrix Rotate(float angle, const Vector3& axis);
    static Matrix Rotate(const Vector3& rotation);
    static Matrix Scale(const Vector3& scale);

    static Matrix Perspective(float fov, float aspect, float near, float far);
    static Matrix Orthographic(float left, float right, float bottom, float top);

    static Matrix Inverse(const Matrix& matrix);
    static Matrix Transpose(const Matrix& matrix);

    Matrix operator *(const Matrix& rhs) const;
    Vector4 operator *(const Vector4& rhs) const;

    Vector4 GetRow(int i) const;
  };
}

#endif // !CORE_MATRIX_H