#include "Framebuffer.h"
#include "GL.h"
#include "Log.h"

using namespace Core;

Framebuffer::Framebuffer()
{
  glGenFramebuffers(1, &id);
  glBindFramebuffer(GL_FRAMEBUFFER, id);
}

Framebuffer::~Framebuffer()
{
  glDeleteFramebuffers(1, &id);
}

void Framebuffer::Attach(Texture* texture, int output)
{
  int attachment;

  switch (output)
  {
  case FRAMEBUFFER_OUTPUT_DEPTH:
    attachment = GL_DEPTH_ATTACHMENT;
    break;
  case FRAMEBUFFER_OUTPUT_STENCIL:
    attachment = GL_STENCIL_ATTACHMENT;
    break;
  default:
    attachment = GL_COLOR_ATTACHMENT0 + (output - FRAMEBUFFER_OUTPUT_COLOR);
    attachments++;
    break;
  }
  
  glBindFramebuffer(GL_FRAMEBUFFER, id);
  glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->GetIdentity(), 0);
}

String Framebuffer::GetLog() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	auto message = "";

	switch (status)
	{
	case GL_FRAMEBUFFER_UNDEFINED:											message = "GL_FRAMEBUFFER_UNDEFINED"; break;
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:					message = "Framebuffer has incomplete attachment(s)"; break;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:	message = "Framebuffer must have atleast one attachment"; break;

#ifndef ANDROID
	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:					message = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"; break;
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:					message = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"; break;
#endif // !ANDROID

	case GL_FRAMEBUFFER_UNSUPPORTED:										message = "Framebuffer's attachment combination is unsupported"; break;
	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:					message = "Framebuffer's attachments must have same multisample settings"; break;
	case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:				message = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"; break;
	case GL_FRAMEBUFFER_COMPLETE:												message = "Framebuffer is complete"; break;
	default:																						message = "ERROR"; break;
	}

	return String("Status: ") + message;
}

bool Framebuffer::IsValid() const
{
  glBindFramebuffer(GL_FRAMEBUFFER, id);
  return id != 0 && glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

uint32_t Framebuffer::GetIdentity() const
{
  return id;
}

void Framebuffer::Use()
{
  glBindFramebuffer(GL_FRAMEBUFFER, id);

  List<uint32_t> buffers;

  for (uint32_t i = 0; i < attachments; i++)
  {
    buffers.push_back(GL_COLOR_ATTACHMENT0 + i);
  }

  glDrawBuffers(attachments, buffers.data());
}