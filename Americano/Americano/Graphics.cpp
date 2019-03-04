#include "Graphics.h"

#define GLX_GLXEXT_PROTOTYPES

#include <GL/glew.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#include <Log.h>
#include <stdio.h>
#include <X11/Xlib.h>

using namespace Core;

XDisplay Graphics::Display;
GLXFBConfig* Graphics::Config;
void* Graphics::Visual;

void Graphics::Initialize()
{
  // Open the main display
  Graphics::Display = XOpenDisplay(0);

  if (!Graphics::Display)
  {
    PERROR("ERROR_OPEN_DISPLAY: (Couldn't open main display)");
    throw;
  }

  int major, minor;
  int count;

  // Make sure GLX version is 1.3 or higher
  if (!glXQueryVersion(Graphics::Display, &major, &minor) || (major < 1) || (major == 1 && minor < 3))
  {
    PERROR("ERROR_GLX_VERSION: (GLX version must be 1.3 or higher)");
    throw;
  }

  int attributes[] =
  {
    GLX_X_RENDERABLE    , True,
    GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
    GLX_RENDER_TYPE     , GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
    GLX_RED_SIZE        , 8,
    GLX_GREEN_SIZE      , 8,
    GLX_BLUE_SIZE       , 8,
    GLX_ALPHA_SIZE      , 8,
    GLX_DEPTH_SIZE      , 24,
    GLX_STENCIL_SIZE    , 8,
    GLX_DOUBLEBUFFER    , True,
    None
  };

  // Choose visual settings based on the requirements
  Graphics::Config = glXChooseFBConfig(Graphics::Display, DefaultScreen(Graphics::Display), attributes, &count);

  if (!Graphics::Config)
  {
    PERROR("ERROR_CHOOSE_VISUAL: (Couldn't find suitable visual settings)");
    throw;
  }

  Graphics::Visual = static_cast<void*>(glXGetVisualFromFBConfig(Graphics::Display, *Graphics::Config));

  // Create a dummy context in order to initialize GLEW
  GLXContext context = glXCreateContext(Graphics::Display, static_cast<XVisualInfo*>(Graphics::Visual), 0, true);

  // Bind the created dummy context
  glXMakeCurrent(Graphics::Display, 0, context);

  // Enable experimental features
  glewExperimental = true;

  // Try to initialize GLEW
  if (glewInit() != GLEW_OK)
  {
    PERROR("ERROR_INITIALIZE_GRAPHICS: (Couldn't initialize GLEW)");

    // Destroy the dummy context
    glXMakeCurrent(Graphics::Display, 0, 0);
    glXDestroyContext(Graphics::Display, context);

    throw;
  }

  // Destroy the dummy context
  glXMakeCurrent(Graphics::Display, 0, 0);
  glXDestroyContext(Graphics::Display, context);

  SUCCESS("Graphics: OK");
}
