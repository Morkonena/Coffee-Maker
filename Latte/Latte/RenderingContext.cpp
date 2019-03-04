#include "RenderingContext.h"
#include "Window.h"

#include <GL\glew.h>
#include <GL\wglew.h>

#include <Log.h>

#include <thread>

using namespace Core;

#define MAX_UNBIND_TRIES 10

RenderingContext::RenderingContext()
{}

RenderingContext::RenderingContext(const Window* window, const RenderingContext* share)
{
  this->window = window;

  const int attributes[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 5,
    WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
    0
  };

  // Create a rendering context capable of using OpenGL 3.x or later
  handle = wglCreateContextAttribsARB(window->GetDeviceContext(), (share ? share->handle : 0), attributes);
	
  if (!handle)
  {
    PERROR("ERROR_CREATE_RENDERING_CONTEXT (", GetLastError(), ")");
    throw;
  }
}

RenderingContext::RenderingContext(RenderingContext&& rendering_context)
{
  this->handle = rendering_context.handle;
  this->window = rendering_context.window;

  rendering_context.handle = 0;
  rendering_context.window = 0;
}

RenderingContext& RenderingContext::operator=(RenderingContext&& rendering_context)
{
  this->handle = rendering_context.handle;
  this->window = rendering_context.window;

  rendering_context.handle = 0;
  rendering_context.window = 0;

  return *this;
}

RenderingContext::~RenderingContext()
{
  if (handle)
  {
    wglMakeCurrent(0, 0);
    wglDeleteContext(handle);
  }
}

bool RenderingContext::Bind()
{
  return wglMakeCurrent(window->GetDeviceContext(), handle) == TRUE;
}

bool RenderingContext::Unbind()
{
  return wglMakeCurrent(0, 0) == TRUE;
}
