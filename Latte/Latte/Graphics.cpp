#include <GL.h>
#include <Log.h>

#include <Windows.h>

#include "Graphics.h"

using namespace Core;

LRESULT CALLBACK OnWindowEvent(HWND window_handle, UINT message, WPARAM w, LPARAM l);

void Graphics::Initialize()
{
  // Get handle to this application
  HINSTANCE instance = GetModuleHandle(0);

  if (!instance)
  {
    PERROR("ERROR_NULL_APPLICATION_HANDLE (", GetLastError(), ")");
    throw;
  }

  // Create window settings
  WNDCLASSA window_info = {};
  window_info.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
  window_info.hInstance = instance;
  window_info.lpfnWndProc = OnWindowEvent;
  window_info.lpszClassName = "Latte";
  window_info.style = CS_OWNDC;

  // Register a window
  if (!RegisterClass(&window_info))
  {
    PERROR("ERROR_REGISTER_WINDOW (", GetLastError(), ")");
    throw;
  }

  // Create the window
  HWND window_handle = CreateWindow("Latte", "", WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, 0, 0, instance, 0);

  if (!window_handle)
  {
    PERROR("ERROR_CREATE_WINDOW");
    throw;
  }

  // Retrieve device context for the window
  HDC device_context = GetDC(window_handle);

  // Create pixel format settings
  PIXELFORMATDESCRIPTOR format_descriptor = {};
  format_descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  format_descriptor.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
  format_descriptor.iPixelType = PFD_TYPE_RGBA;
  format_descriptor.cColorBits = 32;
  format_descriptor.cDepthBits = 24;
  format_descriptor.cStencilBits = 8;

  // Choose a pixel format based on the settings
  int format = ChoosePixelFormat(device_context, &format_descriptor);

  if (format == 0)
  {
    PERROR("ERROR_CHOOSE_PIXEL_FORMAT (", GetLastError(), ")");
    throw;
  }

  // Bind the pixel format
  if (SetPixelFormat(device_context, format, &format_descriptor) != TRUE)
  {
    PERROR("ERROR_SET_PIXEL_FORMAT (", GetLastError(), ")");
    throw;
  }

  // Create a helper context to initialize OpenGL with extensions
  HGLRC rendering_context = wglCreateContext(device_context);

  if (!rendering_context)
  {
    PERROR("ERROR_CREATE_CONTEXT (", GetLastError(), ")");
    throw;
  }

  // Bind the rendering context
  if (wglMakeCurrent(device_context, rendering_context) != TRUE)
  {
    PERROR("ERROR_MAKE_CURRENT (", GetLastError(), ")");
    throw;
  }
  
  // Enable extensions
  glewExperimental = true;

  if (glewInit() != GLEW_OK)
  {
    PERROR("ERROR_INITIALIZE_GLEW");
    throw;
  }

  // Delete the helper context
  wglMakeCurrent(0, 0);
  wglDeleteContext(rendering_context);

  // Destroy the window
  DestroyWindow(window_handle);

  // Unregister the window class
  UnregisterClass("Latte", instance);

  SUCCESS("Graphics: OK");
}
