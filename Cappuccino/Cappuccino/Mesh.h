//
// Created by Mörkönenä on 9.7.2018
//

#ifndef CORE_MESH_H
#define CORE_MESH_H

#include "Camera.h"
#include "Buffer.h"
#include "Vector2.h"
#include "Vector3.h"

namespace Core
{
  enum BufferTarget : int
  {
		BUFFER_TARGET_INDICES = -1,
    BUFFER_TARGET_VERTICES,
    BUFFER_TARGET_UVS,
    BUFFER_TARGET_NORMALS,
		BUFFER_TARGET_COLORS,
    BUFFER_TARGET_CUSTOM,
  };

  enum BufferElement : int
  {
    BUFFER_ELEMENT_FLOAT = 1,
    BUFFER_ELEMENT_VECTOR2 = 2,
    BUFFER_ELEMENT_VECTOR3 = 3,
    BUFFER_ELEMENT_VECTOR4 = 4
  }; 

  class Mesh
  {
	private:
		uint32_t id;

  private:
    class MeshBuffer : public Buffer
    {    
    private:
      BufferTarget target;
			BufferElement element;

    public:
      using Buffer::Buffer;

      void SetTarget(BufferTarget target);
      void SetElement(BufferElement element);

      BufferTarget GetTarget() const;
      BufferElement GetElement() const;
    };

  private:
    mutable List<Managed<MeshBuffer>> buffers;

  public:
    Mesh() = default;
    Mesh(Mesh&& mesh) = default;
    Mesh& operator=(Mesh&& mesh) = default;
    ~Mesh();

    Buffer& CreateBuffer(BufferTarget target, BufferElement element = BUFFER_ELEMENT_VECTOR3, BufferUsage usage = BUFFER_USAGE_STATIC);
    
    Buffer* GetBuffer(BufferTarget target) const;
    Buffer& GetBufferAt(int i) const;

		bool HasBuffer(BufferTarget target) const;
    
    int GetBufferCount();

    bool Upload();
    void Use() const;
  };
}

#endif // !CORE_MESH_H