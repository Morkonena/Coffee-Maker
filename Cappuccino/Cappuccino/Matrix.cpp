#include "Matrix.h"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

using namespace Core;

/* Constant-Cast-Coffee */
#define CCC(X) *reinterpret_cast<const Matrix*>(&(X))
/* Cast-Coffee */
#define CC(X) *reinterpret_cast<Matrix*>(&(X))
/* Constant-Cast-Glm */
#define CCG(X) *reinterpret_cast<const glm::mat4*>(&(X))
/* Cast-Glm */
#define CG(X) *reinterpret_cast<const glm::mat4*>(&(X))

Matrix::Matrix() {}
Matrix::Matrix(const float* data)
{
  rows[0] = *(Vector4*)data;
  rows[1] = *(Vector4*)&data[4];
  rows[2] = *(Vector4*)&data[8];
  rows[3] = *(Vector4*)&data[12];
}

Matrix Matrix::GetIdentity(float i)
{
	auto matrix = glm::mat4(i);
  return CC(matrix);
}

Matrix Matrix::Translate(const Vector3& translation)
{
	auto matrix = glm::translate(glm::mat4(1.0f), *reinterpret_cast<const glm::vec3*>(&translation));
  return CC(matrix);
}

Matrix Matrix::Rotate(float angle, const Vector3& axis)
{
	auto matrix = glm::rotate(glm::mat4(1.0f), angle, *reinterpret_cast<const glm::vec3*>(&axis));
  return CC(matrix);
}

Matrix Matrix::Rotate(const Vector3& rotation)
{
  return Rotate(rotation.z, Vector3(0, 0, 1)) * Rotate(rotation.y, Vector3(0, 1, 0)) * Rotate(rotation.x, Vector3(1, 0, 0));
}

Matrix Matrix::Scale(const Vector3& scale)
{
	auto matrix = glm::scale(glm::mat4(1.0f), *reinterpret_cast<const glm::vec3*>(&scale));
  return CC(matrix);
}

Matrix Matrix::Perspective(float fov, float aspect, float near, float far)
{
	auto matrix = glm::perspectiveLH(fov, aspect, near, far);
  return CC(matrix);
}

Matrix Matrix::Orthographic(float left, float right, float bottom, float top)
{
	auto matrix = glm::ortho(left, right, bottom, top);
  return CC(matrix);
}

Matrix Matrix::Inverse(const Matrix& m)
{
	auto matrix = glm::inverse(CCG(m));
  return CC(matrix);
}

Matrix Matrix::Transpose(const Matrix& m)
{
	auto matrix = glm::transpose(CCG(m));
  return CC(matrix);
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
	auto matrix = CCG(*this) * CCG(rhs);
  return CC(matrix);
}

Vector4 Matrix::operator*(const Vector4& rhs) const
{
  auto vector = CCG(*this) * (*reinterpret_cast<const glm::vec4*>(&rhs));
  return *reinterpret_cast<Vector4*>(&vector);
}

Vector4 Matrix::GetRow(int i) const
{
  return rows[i];
}
