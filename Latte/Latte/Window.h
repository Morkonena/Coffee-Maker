//
// Created by Mörkönenä on 10.7.2018
//

#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <Standard.h>

#include "RenderingContext.h"
#include "Vector2.h"

typedef struct HWND__* WindowHandle;
typedef struct HDC__* DeviceContext;

namespace Core
{
  class Window
  {
  private:
    int width;
    int height;

    String name;

    mutable WindowHandle window_handle		= nullptr;
    mutable DeviceContext device_context	= nullptr;
    mutable RenderingContext rendering_context;

    bool locked = false;

    void Process();

  public:
    Window(int width, int height, bool fullscreen = true, std::string title = "");
    ~Window();

		void Start	();
    void Show		();
    void Hide		();
		void Close	();

		bool SetVSync(bool on);

    void SetCursorVisible		(bool visible);
    void SetCursorLocked		(bool locked);
    void SetCursorPosition	(Vector2 position);

    int GetWidth	() const;
    int GetHeight	() const;

    DeviceContext GetDeviceContext() const;
    RenderingContext& GetRenderingContext() const;

    bool IsClosing() const;

    void Update();
  };
}

#endif // !CORE_WINDOW_H