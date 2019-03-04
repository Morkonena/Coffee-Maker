//
// Created by Mörkönenä on 16.10.2018
//

#ifndef CORE_RENDERING_CONTEXT_H
#define CORE_RENDERING_CONTEXT_H

struct __GLXcontextRec;

namespace Core
{
  class RenderingContext
  {
  private:
    __GLXcontextRec* handle;
    const class Window* window;

  public:
    RenderingContext();
    RenderingContext(const Window* window, const RenderingContext* share = nullptr);
    RenderingContext(RenderingContext&& context);
    RenderingContext& operator=(RenderingContext&& context);
    ~RenderingContext();

    bool Bind();
    bool Unbind();
  };
}

#endif // !CORE_RENDERING_CONTEXT_H
