//
// Created by Mörkönenä on 10.7.2018
//

#ifndef CORE_EFFECT_H
#define CORE_EFFECT_H

#include "Matrix.h"
#include "Shader.h"
#include "Standard.h"
#include "Texture.h"
#include "TextureArray.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Core
{
  typedef std::int32_t Sampler;

  class Effect
  {
	private:
		uint32_t id;

  private:   
    Map<String, Sampler> samplers;
		Sampler GetSampler (std::string name);

  public:
    Effect(Parameters<Shader*> shaders);

    bool IsValid() const;

    String GetLog() const;
		uint32_t GetIdentity() const;

    void Use();

    void Set(const char* variable, int						value);
    void Set(const char* variable, float					value);
		void Set(const char* variable, Vector2 				value);
    void Set(const char* variable, Vector3 				value);
    void Set(const char* variable, Vector4 				value);
    void Set(const char* variable, Matrix&				value);
		void Set(const char* variable, Texture&				value);
		void Set(const char* variable, TextureArray&	value);
  };
}

#endif // !CORE_EFFECT_H