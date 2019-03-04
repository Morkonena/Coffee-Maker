//
// Created by Mörkönenä on 17.7.2018
//

#ifndef CORE_TEXTURE_H
#define CORE_TEXTURE_H

#include "Standard.h"

namespace Core
{
  enum TextureFormat
  {
    TEXTURE_FORMAT_RGB8,
    TEXTURE_FORMAT_RGB32,
    TEXTURE_FORMAT_RGBA8,
    TEXTURE_FORMAT_RGBA32,
    TEXTURE_FORMAT_D24S8,
		TEXTURE_FORMAT_FLOAT,
		TEXTURE_FORMAT_INT,
		TEXTURE_FORMAT_UINT
  };

	enum TextureWrapping
	{
		TEXTURE_WRAPPING_CLAMP,
		TEXTURE_WRAPPING_REPEAT,
		TEXTURE_WRAPPING_MIRRORED_REPEAT
	};

  class Texture
  {
  private:
    uint32_t id;

    TextureFormat format;

    int width;
    int height;

    void* pixels;

  public:
    Texture();
    Texture(Texture&& texture);
    Texture& operator=(Texture&& texture);
    ~Texture();

    bool IsValid();

    void SetPixels(TextureFormat format, int width, int height, void* pixels);
		void Apply();

		void SetSmoothing (bool on);
		void SetWrapping  (TextureWrapping mode);
		void SetWrappingX (TextureWrapping mode);
		void SetWrappingY (TextureWrapping mode);

    TextureFormat GetFormat() const;

    int GetWidth() const;
    int GetHeight() const;

    void* GetPixels() const;

		uint32_t GetIdentity() const;
  };
}

#endif // !CORE_TEXTURE_H