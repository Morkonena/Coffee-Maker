#include <GL.h>
#include <Log.h>

#include <GL\wglew.h>
#include <sstream>
#include <Windows.h>
#include <windowsx.h>

#include <Input.h>

#include "Graphics.h"
#include "Window.h"

using namespace Core;

#define GET_LPX(X) static_cast<float>(GET_X_LPARAM(X))
#define GET_LPY(X) static_cast<float>(GET_Y_LPARAM(X))

static bool Closing = false;

extern LRESULT CALLBACK OnWindowEvent(HWND window, UINT message, WPARAM w, LPARAM l)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		Input::Feed(0, GET_LPX(l), GET_LPY(l), true);
		break;
	case WM_LBUTTONUP:
		Input::Feed(0, GET_LPX(l), GET_LPY(l), false);
		break;
	case WM_RBUTTONDOWN:
		Input::Feed(1, GET_LPX(l), GET_LPY(l), true);
		break;
	case WM_RBUTTONUP:
		Input::Feed(1, GET_LPX(l), GET_LPY(l), false);
		break;
	case WM_MOUSEMOVE:
		Input::Feed(0, GET_LPX(l), GET_LPY(l));
		Input::Feed(1, GET_LPX(l), GET_LPY(l));
		break;
	case WM_MOUSELEAVE:
		Input::OnCursorLeave();
		break;
	case WM_KEYDOWN:
		Input::Feed(static_cast<VirtualKey>(w), true);
		break;
	case WM_KEYUP:
		Input::Feed(static_cast<VirtualKey>(w), false);
		break;
	case WM_CLOSE:
	case WM_QUIT:
		Closing = true;
		break;
	default:
		break;
	}

  return DefWindowProc(window, message, w, l);
}

void Window::Process()
{
  MSG msg = {};

  // Process all messages until there's none
  while (PeekMessage(&msg, window_handle, 0, 0, PM_REMOVE) > 0)
  {
    DispatchMessage(&msg);
  }
}

Window::Window(int width, int height, bool fullscreen, std::string title)
{
  this->width = width;
  this->height = height;

  // Get handle to this application
  HINSTANCE instance = GetModuleHandle(0);

  // Create unique name for this window
  std::stringstream stream;
  stream << "Latte";

  // Save the name for later use
  name = stream.str();

  // Create window settings
  WNDCLASSA window_info = {};
  window_info.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
  window_info.hInstance = instance;
  window_info.lpfnWndProc = OnWindowEvent;
  window_info.lpszClassName = name.c_str();
  window_info.style = CS_OWNDC;

  // Register this window
  if (!RegisterClass(&window_info))
  {
    PERROR("ERROR_REGISTER_WINDOW");
    throw;
  }

  // Create this window
  window_handle = CreateWindow(name.c_str(), title.c_str(), fullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW, 0, 0, width, height, 0, 0, instance, 0);

  if (!window_handle)
  {
    PERROR("ERROR_CREATE_WINDOW");
    throw;
  }

  // Retrieve device context for this window
  device_context = GetDC(window_handle);
  
  if (!device_context)
  {
    PERROR("ERROR_DEVICE_CONTEXT");
    throw;
  }

  // Create settings for pixel format
  PIXELFORMATDESCRIPTOR format_descriptor = {};
  format_descriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  format_descriptor.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
  format_descriptor.iPixelType = PFD_TYPE_RGBA;
  format_descriptor.cColorBits = 32;
  format_descriptor.cDepthBits = 24;
  format_descriptor.cStencilBits = 8;

  // Create settings for pixel format
  const int format_attributes[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
    WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
    WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 24,
    WGL_STENCIL_BITS_ARB, 8,
    0
  };

	/*
		WGL_SAMPLE_BUFFERS_ARB, 1,
		WGL_SAMPLES_ARB, 1,
	*/
  
  int32_t  format;
  uint32_t format_count;

  // Choose a pixel format based on the settings
  if (wglChoosePixelFormatARB(device_context, format_attributes, 0, 1, &format, &format_count) != TRUE)
  {
    PERROR("ERROR_CHOOSE_PIXEL_FORMAT");
    throw;
  }
	
  // Set the pixel format to the chosen one
  if (SetPixelFormat(device_context, format, &format_descriptor) != TRUE)
  {
    PERROR("ERROR_SET_PIXEL_FORMAT");
    throw;
  }

  // Initialize the rendering context
  rendering_context = RenderingContext(this);
 
  Process();
}

Window::~Window()
{
  DestroyWindow(window_handle);
}

void Window::Start()
{
	Show();

	if (!GetRenderingContext().Bind())
	{
		PERROR("ERROR_START_WINDOW");
		throw;
	}
}

void Window::Show()
{
  ShowWindow(window_handle, SW_SHOW);
}

void Window::Hide()
{
  ShowWindow(window_handle, SW_HIDE);
}

void Window::Close()
{
	PostQuitMessage(0);
}

bool Window::SetVSync(bool on)
{
	return wglSwapIntervalEXT(on ? 1 : 0) == TRUE;
}

void Window::SetCursorPosition(Vector2 position)
{
  SetCursorPos((int)position.x, (int)position.y);
}

void Window::SetCursorVisible(bool visible)
{
  ShowCursor(visible);
}

void Window::SetCursorLocked(bool locked)
{
  this->locked = locked;
}

int Window::GetWidth() const
{
  return width;
}

int Window::GetHeight() const
{
  return height;
}

DeviceContext Window::GetDeviceContext() const
{
  return device_context;
}

RenderingContext& Window::GetRenderingContext() const
{
  return rendering_context;
}

bool Window::IsClosing() const
{
  return Closing;
}

void Window::Update()
{
  SwapBuffers(device_context);

  Process();

  if (locked)
  {
    SetCursorPosition(Vector2(width, height) * 0.5f);
  }
}
