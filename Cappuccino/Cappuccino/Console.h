//
// Created by M�rk�nen� on 16.10.2018
//

#ifndef CORE_CONSOLE_H
#define CORE_CONSOLE_H

#ifdef ANDROID
#include <sstream>
#include <android/log.h>
#else // WINDOWS & LINUX
#include <iostream>
#endif // ANDROID

namespace Core
{
	enum ConsoleMode
	{
		CONSOLE_MODE_NORMAL,
		CONSOLE_MODE_SUCCESS,
		CONSOLE_MODE_WARNING,
		CONSOLE_MODE_ERROR
	};

  class Console
  {
  private:
    template<typename A, typename... B>
    static void Continue(A& a, B&... list);

    static inline void Continue() {};

#ifdef ANDROID
		static int Mode;

#else // WINDOWS & LINUX
#ifdef LINUX
		// ...
#else // WINDOWS
		static void* Handle;

	public:
		static void Initialize();
#endif // LINUX
#endif // ANDROID

  public:
		static void SetMode(ConsoleMode mode);

    template<typename... T>
    static void Write(T&&... list);

    template<typename... T>
    static void WriteLine(T&&... list);
  };

  template<typename A, typename ...B>
  inline void Console::Continue(A& a, B&... list)
  {
#ifdef ANDROID
		std::stringstream stream;
		stream << a;

		__android_log_write(Mode, "Coffee", stream.str().c_str());
#else // WINDOWS & LINUX
		std::cout << a;
#endif // ANDROID

    Continue(list...);
  }

  template<typename... T>
  inline void Console::Write(T&&... list)
  {
    Continue(list...);
  }

  template<typename ...T>
  inline void Console::WriteLine(T&&... list)
  {
    Continue(list...);

#ifdef ANDROID
		__android_log_write(Mode, "Coffee", "\n");
#else // WINDOWS & LINUX
		std::cout << std::endl;
#endif // !ANDROID
  }
}

#endif // !CORE_CONSOLE_H
