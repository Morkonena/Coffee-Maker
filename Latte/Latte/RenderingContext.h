//
// Created by Mörkönenä on 16.10.2018
//

#ifndef CORE_RENDERING_CONTEXT_H
#define CORE_RENDERING_CONTEXT_H

typedef struct HGLRC__* HGLRC;

namespace Core
{
  class RenderingContext
  {
  private:
    HGLRC handle;
    const class Window* window;

  public:
    RenderingContext();
    RenderingContext(const Window* window, const RenderingContext* share = nullptr);
    RenderingContext(RenderingContext&& rendering_context);
    RenderingContext& operator=(RenderingContext&& rendering_context);
    ~RenderingContext();

    bool Bind();
    bool Unbind();
  };

}

#endif // !CORE_RENDERING_CONTEXT_H

