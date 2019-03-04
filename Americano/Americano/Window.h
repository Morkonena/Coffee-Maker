//
// Created by Mörkönenä on 18.1.2019
//

#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "RenderingContext.h"
#include "Standard.h"

typedef unsigned long XHandle;

namespace Core
{
  class Window
  {
  private:
    friend class Graphics;
    friend class RenderingContext;

    XHandle handle;
    XHandle colormap;

    Managed<RenderingContext> context;

    bool closing = false;

  public:
    Window (int width, int height, String title = "");

    void Start	();
    void Show		();
    void Hide		();
    void Close	();

    void SetFullscreen (bool fullscreen);

    // bool SetVSync(bool on);

    // void SetCursorVisible		(bool visible);
    // void SetCursorLocked		(bool locked);
    // void SetCursorPosition	(Vector2 position);

    int GetWidth	() const;
    int GetHeight	() const;

    RenderingContext& GetRenderingContext() const;

    bool IsClosing() const;

    void Update();
  };
}

#endif
