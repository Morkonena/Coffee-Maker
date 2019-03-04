//
// Created by Mörkönenä on 3.9.2018
//

#ifndef CORE_TEXTURE_ARRAY_H
#define CORE_TEXTURE_ARRAY_H

#include "Standard.h"
#include "Texture.h"

namespace Core
{
  class TextureArray
  {
  private:
    uint32_t id;

    TextureFormat format;

    int width;
    int height;
    int length;

  public:
    TextureArray(TextureFormat format, int width, int height, int length);
    TextureArray(TextureArray&& texture_array);
    TextureArray& operator=(TextureArray&& texture_array);
    ~TextureArray();

    void Set(int i, const Texture& texture);

		void SetSmoothing(bool enable);
		void SetWrapping(TextureWrapping mode);
		void SetWrappingX(TextureWrapping mode);
		void SetWrappingY(TextureWrapping mode);

    TextureFormat GetFormat() const;

    int GetWidth() const;
    int GetHeight() const;

    int GetLength() const;

		uint32_t GetIdentity() const;
  };
}

#endif // !CORE_TEXTURE_ARRAY