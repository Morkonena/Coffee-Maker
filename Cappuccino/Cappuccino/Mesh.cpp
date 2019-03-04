#include "Mesh.h"
#include "GL.h"

using namespace Core;

bool Mesh::Upload()
{
  glGenVertexArrays(1, &id);
  glBindVertexArray(id);

  for (auto& i : buffers)
  {
    MeshBuffer& buffer = *i;
    buffer.Use();

    if (buffer.GetTarget() == BUFFER_TARGET_INDICES)
    {
      continue;
    }
		
    glVertexAttribPointer(buffer.GetTarget(), buffer.GetElement(), GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(buffer.GetTarget());
  }

  glBindVertexArray(0);
  return true;
}

void Mesh::Use() const
{
  glBindVertexArray(id);
}

Mesh::~Mesh()
{
  glDeleteVertexArrays(1, &id);
}

Buffer& Mesh::CreateBuffer(BufferTarget target, BufferElement element, BufferUsage usage)
{
  BufferType type = (target == BUFFER_TARGET_INDICES) ? BUFFER_TYPE_INDEX : BUFFER_TYPE_DATA;

  Managed<MeshBuffer> buffer = std::make_unique<MeshBuffer>(type, usage);
  buffer->SetTarget(target);
  buffer->SetElement(element);

  MeshBuffer* address = buffer.get();
  buffers.push_back(std::move(buffer));

  return *address;
}

Buffer* Mesh::GetBuffer(BufferTarget target) const
{
  auto i = std::find_if(buffers.begin(), buffers.end(), [target](std::unique_ptr<MeshBuffer>& x) { return x->GetTarget() == target; });
  return (i == buffers.end()) ? nullptr : i->get();
}

Buffer& Mesh::GetBufferAt(int i) const
{
  return *buffers[i];
}

bool Mesh::HasBuffer(BufferTarget target) const
{
	return std::find_if(buffers.begin(), buffers.end(), [target](std::unique_ptr<MeshBuffer>& x) { return x->GetTarget() == target; }) != buffers.end();
}

int Mesh::GetBufferCount()
{
  return (int)buffers.size();
}

void Mesh::MeshBuffer::SetTarget(BufferTarget target)
{
  this->target = target;
}

void Mesh::MeshBuffer::SetElement(BufferElement input)
{
  this->element = input;
}

BufferTarget Mesh::MeshBuffer::GetTarget() const
{
  return target;
}

BufferElement Mesh::MeshBuffer::GetElement() const
{
  return element;
}
