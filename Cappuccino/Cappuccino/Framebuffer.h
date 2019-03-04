//
// Created by Mörkönenä on 18.9.2018
//

#ifndef CORE_FRAMEBUFFER_H
#define CORE_FRAMEBUFFER_H

#include "Texture.h"

namespace Core
{
  enum FramebufferType
  {
    FRAMEBUFFER_TYPE_COLOR,
    FRAMEBUFFER_TYPE_DEPTH
  };

  enum FramebufferOutput : int 
  {
    FRAMEBUFFER_OUTPUT_DEPTH,
    FRAMEBUFFER_OUTPUT_STENCIL,
    FRAMEBUFFER_OUTPUT_COLOR
  };

  class Framebuffer
  {
  private:
    uint32_t id;
		uint32_t attachments = 0;

  public:
    Framebuffer();
    Framebuffer(Framebuffer&& framebuffer) = default;
    Framebuffer& operator=(Framebuffer&& framebuffer) = default;
    ~Framebuffer();

    bool IsValid() const;

    void Use();
    void Attach(Texture* texture, int output);

		String GetLog() const;
    uint32_t GetIdentity() const;
  };
}

#endif // !CORE_FRAMEBUFFER_H