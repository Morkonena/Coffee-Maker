//
// Created by Mörkönenä on 10.7.2018
//

#ifndef CORE_SHADER_H
#define CORE_SHADER_H

#include "Standard.h"

namespace Core
{
  enum ShaderType : int
  {
    SHADER_TYPE_VERTEX,
    SHADER_TYPE_FRAGMENT
  };

  class Shader
  {
  private:
    uint32_t id;

  public:
    Shader(ShaderType type, std::string text);
    ~Shader();

    bool IsValid() const;

    String GetLog() const;
		uint32_t GetIdentity() const;
  };
}

#endif // !CORE_SHADER_H