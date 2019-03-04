#include "GL.h"
#include "Shader.h"

using namespace Core;

constexpr int types[] =
{
  GL_VERTEX_SHADER,
  GL_FRAGMENT_SHADER
};

Shader::Shader(ShaderType type, std::string text)
{
  id = glCreateShader(types[type]);

  auto address = text.c_str();
  int length = (int)text.length();

  glShaderSource(id, 1, &address, &length);
  glCompileShader(id);
}

Shader::~Shader()
{
  glDeleteShader(id);
}

bool Shader::IsValid() const
{
  if (id == 0)
  {
    return false;
  }

  int i;
  glGetShaderiv(id, GL_COMPILE_STATUS, &i);

  return i == GL_TRUE;
}

String Shader::GetLog() const
{
  int length;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

  List<char> log(length + 1);
  log[length] = 0;

  glGetShaderInfoLog(id, length, &length, log.data());

  return String(log.data());
}

uint32_t Shader::GetIdentity() const
{
  return id;
}
