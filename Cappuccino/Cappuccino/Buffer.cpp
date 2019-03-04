#include "Buffer.h"
#include "GL.h"

using namespace Core;

constexpr int targets[] =
{
  GL_ARRAY_BUFFER,
  GL_ELEMENT_ARRAY_BUFFER,
	GL_SHADER_STORAGE_BUFFER
};

constexpr int usages[] =
{
  GL_STATIC_DRAW,
  GL_DYNAMIC_DRAW,
  GL_STREAM_DRAW
};

constexpr int options[] =
{
  GL_READ_ONLY,
  GL_WRITE_ONLY,
  GL_READ_WRITE
};

Buffer::Buffer(BufferType type, BufferUsage usage)
{
  this->type = type;
  this->usage = usage;

  glGenBuffers(1, &id);
}

Buffer::Buffer(Buffer&& buffer)
{
  this->id = buffer.id;
  this->type = buffer.type;
  this->usage = buffer.usage;

  buffer.id = -1;
}

Buffer& Buffer::operator=(Buffer&& buffer)
{
  this->id = buffer.id;
  this->type = buffer.type;
  this->usage = buffer.usage;

  buffer.id = -1;

  return *this;
}

Buffer::~Buffer()
{
  if (id > 0)
  {
    glDeleteBuffers(1, &id);
  }
}

bool Buffer::IsValid() const
{
  return (id != 0);
}

void Buffer::Use()
{
  glBindBuffer(targets[(int)type], id);
}

void Buffer::SetData(const void* data, int size)
{
  const int target = targets[(int)this->type];
  const int usage = usages[(int)this->usage];
  
  glBindBuffer(target, id);
  glBufferData(target, size, data, usage);

  this->size = size;
}

int Buffer::GetSize() const
{
  return size;
}

void* Buffer::Map(BufferAccess access)
{
  const int target = targets[(int)type];
  const int option = options[(int)access];

  glBindBuffer(target, id);
	return glMapBufferRange(target, 0, size, option);
}

void Buffer::Unmap()
{
  const int target = targets[(int)type];
  
  glBindBuffer(target, id);
  glUnmapBuffer(target);
}

uint32_t Buffer::GetIdentity() const
{
  return id;
}

int Buffer::GetType() const
{
  return type;
}

int Buffer::GetUsage() const
{
  return usage;
}
