//
// Created by Mörkönenä on 10.7.2018
//

#ifndef CORE_SCREEN_H
#define CORE_SCREEN_H

namespace Core
{
  class Screen
  {
	public:
    static int GetWidth();
    static int GetHeight();

    static float GetAspect();
	};
}

#endif // !CORE_SCREEN_H