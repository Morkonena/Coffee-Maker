#include "RenderingContext.h"
#include "Window.h"
#include "Graphics.h"

#define GLX_GLXEXT_PROTOTYPES

#include <GL/glx.h>
#include <GL/glxext.h>
#include <Log.h>

using namespace Core;

RenderingContext::RenderingContext() {}
RenderingContext::RenderingContext(const Window* window, const RenderingContext* share) : window(window)
{
  int attributes[] =
  {
    GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
    GLX_CONTEXT_MINOR_VERSION_ARB, 2,
    GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
    None
  };

  handle = glXCreateContextAttribsARB(Graphics::Display, *Graphics::Config, 0, True, attributes);

  if (!handle)
  {
    PERROR("ERROR_CREATE_CONTEXT");
    throw;
  }
}

RenderingContext::RenderingContext(RenderingContext&& rhs)
{
  handle = rhs.handle;
  window = rhs.window;

  rhs.handle = 0;
  rhs.window = 0;
}

RenderingContext& RenderingContext::operator=(RenderingContext&& rhs)
{
  handle = rhs.handle;
  window = rhs.window;

  rhs.handle = 0;
  rhs.window = 0;

  return *this;
}

RenderingContext::~RenderingContext()
{
  if (handle)
  {
    glXMakeCurrent(Graphics::Display, None, 0);
    glXDestroyContext(Graphics::Display, handle);
  }
}

bool RenderingContext::Bind()
{
  return glXMakeCurrent(Graphics::Display, window->handle, handle) == True;
}

bool RenderingContext::Unbind()
{
  return glXMakeCurrent(Graphics::Display, None, 0) == True;
}
