//
// Created by Mörkönenä on 9.7.2018
//

#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include "Matrix.h"
#include "Vector3.h"

namespace Core
{
	enum DrawMode : int
	{
		DRAW_MODE_TRIANGLES,
		DRAW_MODE_QUADS,
		DRAW_MODE_LINES
	};

	enum ClearFlags : int
	{
		CLEAR_BACKGROUND,
		CLEAR_DEPTH,
		CLEAR_BOTH
	};

  class Camera
  {
	private:
		static Matrix projection;
		static Matrix view;

	public:
    static void Initialize();

    static Vector3 position;
    static Vector3 rotation;

    static void SetDepth(bool enable);
    static void SetDithering(bool enable);
    static void SetTransparency(bool enable);
    static void SetWindingOrder(bool clockwise);
    static void SetCullFace(bool back);
    static void SetViewport(int x, int y, int width, int height);
    static void SetLineThickness(float thickness);
		static void SetProjection(const Matrix& projection);

    static void Begin();
    static void Clear(Vector4 color, ClearFlags flags);

    static void Draw(DrawMode mode, bool indexed, int count);
    static void DrawInstanced(DrawMode mode, bool indexed, int count, int instances);

    static void End();

    static Matrix GetProjection();
    static Matrix GetView();
	};
}

#endif // !CORE_CAMERA_H