#include "GL.h"
#include "Log.h"
#include "TextureArray.h"

using namespace Core;

static constexpr int internals[] =
{
	GL_RGB8,
	GL_RGB32F,
	GL_RGBA8,
	GL_RGBA32F,
	GL_DEPTH24_STENCIL8,
	GL_R32F,
	GL_R32I,
	GL_R32UI
};

static constexpr int formats[] =
{
	GL_RGB,
	GL_RGB,
	GL_RGBA,
	GL_RGBA,
	GL_DEPTH_STENCIL,
	GL_RED,
	GL_RED_INTEGER,
	GL_RED_INTEGER
};

static constexpr int types[] =
{
	GL_UNSIGNED_BYTE,
	GL_FLOAT,
	GL_UNSIGNED_BYTE,
	GL_FLOAT,
	GL_UNSIGNED_INT_24_8,
	GL_FLOAT,
	GL_INT,
	GL_UNSIGNED_INT
};

static constexpr int wrap_modes[] =
{
	GL_CLAMP_TO_EDGE,
	GL_REPEAT,
	GL_MIRRORED_REPEAT
};

TextureArray::TextureArray(TextureFormat format, int width, int height, int length) :
  format(format), width(width), height(height), length(length)
{
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D_ARRAY, id);

  glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, internals[format], width, height, length);
  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

TextureArray::TextureArray(TextureArray&& texture_array)
{
	format	= texture_array.format;
	height	= texture_array.height;
	id			= texture_array.id;
	length	= texture_array.length;
	width		= texture_array.width;

	texture_array.id = 0;
}

TextureArray& TextureArray::operator=(TextureArray&& texture_array)
{
  format	= texture_array.format;
  height	= texture_array.height;
  id			= texture_array.id;
  length	= texture_array.length;
  width		= texture_array.width;

  texture_array.id = 0;

  return *this;
}

TextureArray::~TextureArray()
{
  if (id > 0)
  {
    glDeleteTextures(1, &id);
  }
}

void TextureArray::Set(int i, const Texture& texture)
{
	if (texture.GetWidth() > width || texture.GetHeight() > height || texture.GetFormat() != format)
	{
		PERROR("ERROR_INCOMPATIBLE_TEXTURE: (Texture must fit to texture array's resolution and have the same format)");
		throw;
	}

  glBindTexture(GL_TEXTURE_2D_ARRAY, id);
  glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, formats[format], types[format], texture.GetPixels());
}

void TextureArray::SetSmoothing(bool enable)
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, id);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, enable ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, enable ? GL_LINEAR : GL_NEAREST);
}

void TextureArray::SetWrapping(TextureWrapping mode)
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, id);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, wrap_modes[mode]);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, wrap_modes[mode]);
}

void TextureArray::SetWrappingX(TextureWrapping mode)
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, id);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, wrap_modes[mode]);
}

void TextureArray::SetWrappingY(TextureWrapping mode)
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, id);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, wrap_modes[mode]);
}

TextureFormat TextureArray::GetFormat() const
{
  return format;
}

int TextureArray::GetWidth() const
{
  return width;
}

int TextureArray::GetHeight() const
{
  return height;
}

int TextureArray::GetLength() const
{
  return length;
}

uint32_t TextureArray::GetIdentity() const
{
	return id;
}
