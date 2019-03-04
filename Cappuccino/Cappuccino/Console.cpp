#include "Console.h"
using namespace Core;

#ifndef ANDROID
#ifdef LINUX

void Console::SetMode(ConsoleMode mode)
{
	// TODO: Colors
}

#else // WINDOWS
#include <Windows.h>

HANDLE Console::Handle;

void Console::Initialize()
{
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Console::SetMode(ConsoleMode mode)
{
	switch (mode)
	{
	case Core::CONSOLE_MODE_NORMAL:
		SetConsoleTextAttribute(Handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case Core::CONSOLE_MODE_SUCCESS:
		SetConsoleTextAttribute(Handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case Core::CONSOLE_MODE_WARNING:
		SetConsoleTextAttribute(Handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case Core::CONSOLE_MODE_ERROR:
		SetConsoleTextAttribute(Handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	}
}
#endif // LINUX
#else // ANDROID

int Console::Mode;

void Console::SetMode(ConsoleMode mode)
{
	switch (mode)
	{
	case Core::CONSOLE_MODE_NORMAL:
		Mode = ANDROID_LOG_VERBOSE;
		break;
	case Core::CONSOLE_MODE_SUCCESS:
		Mode = ANDROID_LOG_INFO;
		break;
	case Core::CONSOLE_MODE_WARNING:
		Mode = ANDROID_LOG_WARN;
		break;
	case Core::CONSOLE_MODE_ERROR:
		Mode = ANDROID_LOG_ERROR;
		break;
	}
}

#endif // !ANDROID
