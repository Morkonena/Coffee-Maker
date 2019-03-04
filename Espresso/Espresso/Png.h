//
// Created by Mörkönenä on 18.7.2018
//

#ifndef CORE_PNG_H
#define CORE_PNG_H

#include <Texture.h>
#include <Standard.h>

namespace Core
{
  class Png
  {
	public:
    static Texture* Import(String filename);
	};
}

#endif // !CORE_PNG_H