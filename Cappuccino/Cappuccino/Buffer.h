//
// Created by Mörkönenä on 12.10.2018
//

#ifndef CORE_BUFFER_H
#define CORE_BUFFER_H

#include "Standard.h"

namespace Core
{
  enum BufferType : int
  {
    BUFFER_TYPE_DATA,
    BUFFER_TYPE_INDEX
  };

  enum BufferUsage : int
  {
    BUFFER_USAGE_STATIC,
    BUFFER_USAGE_DYNAMIC,
    BUFFER_USAGE_LOW
  };

  enum BufferAccess : int
  {
    BUFFER_ACCESS_READ,
    BUFFER_ACCESS_WRITE,
    BUFFER_ACCESS_BOTH
  };

  class Buffer
  {
  private:
    uint32_t id = 0;

    int type;
    int usage;

    int size = 0;

  public:
    Buffer(BufferType type = BUFFER_TYPE_DATA, BufferUsage usage = BUFFER_USAGE_STATIC);
    Buffer(Buffer&& buffer);
    Buffer& operator=(Buffer&& buffer);
    ~Buffer();

    bool IsValid() const; 
    void Use();

    void SetData(const void* data, int size);

    template<typename T>
    void SetData(const T* data, int count);

    template<typename T>
    T GetData(int index) const;

    int GetSize() const;

    void* Map(BufferAccess access = BUFFER_ACCESS_BOTH);
    void  Unmap();

    uint32_t GetIdentity() const;

    int GetType() const;
    int GetUsage() const;
  };

  template<typename T>
  inline void Buffer::SetData(const T* data, int count)
  {
    SetData(static_cast<const void*>(data), sizeof(T) * count);
  }

  template<typename T>
  inline T Buffer::GetData(int index) const
  {
    T element;
    GetData(&element, sizeof(T) * index, sizeof(T));

    return element;
  }
}

#endif // !CORE_BUFFER_H