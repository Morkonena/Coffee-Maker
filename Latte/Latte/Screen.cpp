#include "Screen.h"

#include <Windows.h>

int Core::Screen::GetWidth()
{
  return GetSystemMetrics(SM_CXSCREEN);
}

int Core::Screen::GetHeight()
{
  return GetSystemMetrics(SM_CYSCREEN);
}

float Core::Screen::GetAspect()
{
  return GetWidth() / (float)GetHeight();
}
