#include "Window.h"
#include "Camera.h"
#include "Graphics.h"

#include <GL/glx.h>
#include <Log.h>

Core::Window::Window (int width, int height, String title)
{
  XVisualInfo* visual = static_cast<XVisualInfo*>(Graphics::Visual);

  // Get the root window
  ::Window root = RootWindow(Graphics::Display, DefaultScreen(Graphics::Display));

  // Create colormap for the window
  colormap = XCreateColormap(Graphics::Display, root, visual->visual, AllocNone);

  // Define window attributes
  XSetWindowAttributes attributes = {};
  attributes.colormap = colormap;
  attributes.event_mask = ExposureMask | KeyPressMask;

  handle = XCreateWindow(Graphics::Display, root, 0, 0, width, height, 0, visual->depth, InputOutput, visual->visual, CWColormap | CWEventMask, &attributes);

  // Give the window a title
  XStoreName(Graphics::Display, handle, title.c_str());

  // Create a rendering context for this window in order to use OpenGL
  context = std::make_unique<Core::RenderingContext>(this, nullptr);
}

void Core::Window::Start ()
{
  Show();

  if (!context->Bind())
  {
    PERROR("ERROR_START_WINDOW");
		throw;
  }
}

void Core::Window::Show ()
{
  XMapWindow(Graphics::Display, handle);
}

void Core::Window::Hide ()
{
  XUnmapWindow(Graphics::Display, handle);
}

void Core::Window::Close ()
{
  XDestroyWindow(Graphics::Display, handle);
}

void Core::Window::SetFullscreen (bool fullscreen)
{
    Atom state = XInternAtom(Graphics::Display, "_NET_WM_STATE", False);
    Atom property = XInternAtom(Graphics::Display, "_NET_WM_STATE_FULLSCREEN", False);

    XEvent event;
    memset(&event, 0, sizeof(event));
    event.type = ClientMessage;
    event.xclient.window = handle;
    event.xclient.message_type = state;
    event.xclient.format = 32;
    event.xclient.data.l[0] = (fullscreen ? 1 : 0);
    event.xclient.data.l[1] = property;
    event.xclient.data.l[2] = 0;

    XSendEvent(Graphics::Display, DefaultRootWindow(Graphics::Display), False, SubstructureRedirectMask | SubstructureNotifyMask, &event);
    XFlush(Graphics::Display);
}

int Core::Window::GetWidth () const
{
  XWindowAttributes attributes = {};
  XGetWindowAttributes(Graphics::Display, handle, &attributes);
  return attributes.width;
}

int Core::Window::GetHeight () const
{
  XWindowAttributes attributes = {};
  XGetWindowAttributes(Graphics::Display, handle, &attributes);
  return attributes.height;
}

Core::RenderingContext& Core::Window::GetRenderingContext() const
{
  return *context;
}

bool Core::Window::IsClosing () const
{
  return closing;
}

void Core::Window::Update ()
{
  glXSwapBuffers(Graphics::Display, handle);

  int count = XPending(Graphics::Display);

  for (int i = 0; i < count; i++)
  {
    XEvent event;
    XNextEvent(Graphics::Display, &event);

    switch (event.type)
    {
      case LeaveNotify:
      {
        closing = true;
        break;
      }
      case KeyPress:
      {
        // TODO: Events
        break;
      }
      default:
      {
        break;
      }
    }
  }
}
