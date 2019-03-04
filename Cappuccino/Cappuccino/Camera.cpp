#include "Camera.h"
#include "GL.h"

using namespace Core;

Vector3 Camera::position;
Vector3 Camera::rotation;

Matrix Camera::projection;
Matrix Camera::view;

constexpr int modes[] =
{
  GL_TRIANGLES,
  GL_QUADS,
  GL_LINES
};

constexpr int flags[] =
{
  GL_COLOR_BUFFER_BIT,
  GL_DEPTH_BUFFER_BIT,
  GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
};

void Camera::Initialize()
{
  // 1. Depth
  SetDepth(true);

  // 2. Transparency
  SetTransparency(false);
  
  // 3. Winding Order
  SetWindingOrder(false);
}

void Camera::SetDepth(bool enable)
{
  if (enable)
  {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
  }
  else
  {
    glDisable(GL_DEPTH_TEST);
  }
}

void Camera::SetDithering(bool enable)
{
  if (enable)
  {
    glEnable(GL_DITHER);
  }
  else
  {
    glDisable(GL_DITHER);
  }
}

void Camera::SetTransparency(bool enable)
{
  if (enable)
  {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
  else
  {
    glDisable(GL_BLEND);
  }
}

void Camera::SetWindingOrder(bool clockwise)
{
  glFrontFace(clockwise ? GL_CW : GL_CCW);
}

void Camera::SetCullFace(bool back)
{
  glCullFace(back ? GL_BACK : GL_FRONT);
}

void Camera::SetViewport(int x, int y, int width, int height)
{
  glViewport(x, y, width, height);
}

void Camera::SetLineThickness(float thickness)
{
  glLineWidth(thickness);
}

void Camera::Begin()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glBindVertexArray(0);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

  glUseProgram(0);
}

void Camera::Clear(Vector4 color, ClearFlags i)
{
  glClearColor(color.x, color.y, color.z, color.w);
  glClear(flags[i]);
}

void Camera::Draw(DrawMode mode, bool indexed, int count)
{
  if (indexed)
  {
    glDrawElements(modes[mode], count, GL_UNSIGNED_INT, nullptr);
  }
  else
  {
    glDrawArrays(modes[mode], 0, count);
  }
}

void Camera::DrawInstanced(DrawMode mode, bool indexed, int count, int instances)
{
  if (indexed)
  {
    glDrawElementsInstanced(modes[mode], count, GL_UNSIGNED_INT, nullptr, instances);
  }
  else
  {
    glDrawArraysInstanced(modes[mode], 0, count, instances);
  }
}

void Camera::End()
{}

void Camera::SetProjection(const Matrix& projection)
{
  Camera::projection = projection;
}

Matrix Camera::GetProjection()
{
  return projection;
}

Matrix Camera::GetView()
{
  Matrix rotation = Matrix::Rotate(-Camera::rotation.x, Vector3(1, 0, 0)) *
                    Matrix::Rotate(-Camera::rotation.y, Vector3(0, 1, 0)) *  
                    Matrix::Rotate(-Camera::rotation.z, Vector3(0, 0, 1));
  
  Matrix position = Matrix::Translate(Vector3() - Camera::position);

  return rotation * position;
}