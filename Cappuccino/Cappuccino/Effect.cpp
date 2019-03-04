#include "Effect.h"
#include "GL.h"
#include "Log.h"

using namespace Core;

Sampler Effect::GetSampler(std::string name)
{
	Sampler sampler;

	auto i = samplers.find(name);

	if (i == samplers.end())
	{
		int location = glGetUniformLocation(id, name.c_str());

		if (location == -1)
		{
			throw;
		}

		sampler = (Sampler)samplers.size();
		samplers.insert(std::make_pair(name, sampler));

		glUniform1i(location, sampler);
	}
	else
	{
		sampler = i->second;
	}

	return sampler;
}

Effect::Effect(Parameters<Shader*> shaders)
{
  id = glCreateProgram();

  for (Shader* shader : shaders)
  {
    glAttachShader(id, shader->GetIdentity());
  }

  glLinkProgram(id);
}

bool Effect::IsValid() const
{
	int status = GL_FALSE;

  if (id > 0)
  {
		glGetProgramiv(id, GL_LINK_STATUS, &status);
  }

  return status == GL_TRUE;
}

String Effect::GetLog() const
{
  int length;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

  List<char> log(length + 1);
  log[length] = 0;

  glGetProgramInfoLog(id, length, &length, log.data());

  return String(log.data());
}

uint32_t Effect::GetIdentity() const
{
	return id;
}

void Effect::Use()
{
  glUseProgram(id);
}

void Effect::Set(const char* name, int value)
{
  glUniform1i(glGetUniformLocation(id, name), value);
}

void Effect::Set(const char* name, float value)
{
  glUniform1f(glGetUniformLocation(id, name), value);
}

void Effect::Set(const char* name, Vector2 value)
{
	glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}

void Effect::Set(const char* name, Vector3 value)
{
  glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}

void Effect::Set(const char* name, Vector4 value)
{
	glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
}

void Effect::Set(const char* name, Matrix& value)
{
  glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, (float*)&value);
}

void Effect::Set(const char* name, Texture& value)
{
	Sampler sampler;

	try
	{
		sampler = GetSampler(std::string(name));
	}
	catch (...)
	{
		PERROR("ERROR_VARIABLE_NOT_FOUND: uniform sampler2D ", name);
		return;
	}

	glActiveTexture(GL_TEXTURE0 + sampler);
	glBindTexture(GL_TEXTURE_2D, value.GetIdentity());
}

void Effect::Set(const char* name, TextureArray& value)
{
	Sampler sampler;

	try
	{
		sampler = GetSampler(std::string(name));
	}
	catch (...)
	{
		PERROR("ERROR_VARIABLE_NOT_FOUND: uniform sampler2DArray ", name);
		return;
	}

	glActiveTexture(GL_TEXTURE0 + sampler);
	glBindTexture(GL_TEXTURE_2D_ARRAY, value.GetIdentity());
}

