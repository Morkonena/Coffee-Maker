#include "GL.h"
#include "Texture.h"

using namespace Core;

static constexpr int internals[] =
{
  GL_RGB,
  GL_RGB32F,
  GL_RGBA,
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

Texture::Texture()
{
  glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::Texture(Texture&& texture)
{
  format	= texture.format;
  height	= texture.height;
  id			= texture.id;
  pixels	= texture.pixels;
  width		= texture.width;

  texture.id = 0;
}

Texture& Texture::operator=(Texture&& texture)
{
  format	= texture.format;
  height	= texture.height;
  id			= texture.id;
  pixels	= texture.pixels;
  width		= texture.width;

  texture.id = 0;

  return *this;
}

Texture::~Texture()
{
  if (id > 0)
  {
    glDeleteTextures(1, &id);
  }
}

bool Texture::IsValid()
{
  return id > 0;
}

void Texture::SetPixels(TextureFormat format, int width, int height, void* pixels)
{
  this->format = format;
  this->width  = width;
  this->height = height;
  this->pixels = pixels;
  
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, internals[format], width, height, 0, formats[format], types[format], pixels);
}

void Texture::Apply()
{
	if (pixels)
	{
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, internals[format], width, height, 0, formats[format], types[format], pixels);
	}
}

void Texture::SetSmoothing(bool on)
{
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, on ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, on ? GL_LINEAR : GL_NEAREST);

}

void Texture::SetWrapping (TextureWrapping mode)
{
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_modes[mode]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_modes[mode]);
}

void Texture::SetWrappingX (TextureWrapping mode)
{
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_modes[mode]);
}

void Texture::SetWrappingY (TextureWrapping mode)
{
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_modes[mode]);
}

TextureFormat Texture::GetFormat() const
{
  return format;
}

int Texture::GetWidth() const
{
  return width;
}

int Texture::GetHeight() const
{
  return height;
}

void* Texture::GetPixels() const
{
  return pixels;
}

uint32_t Texture::GetIdentity() const
{
	return id;
}

