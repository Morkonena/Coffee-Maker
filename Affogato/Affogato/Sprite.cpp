#include "Sprite.h"
#include "AudioSystem.h"
#include <Actor.h>
#include <Asset.h>
#include <Camera.h>
#include <Log.h>

using namespace Core;

Managed<Effect> Sprite::Effect;
Managed<Mesh> Sprite::Quad;
Set<Sprite*> Sprite::Sprites;

Sprite::Sprite(Actor* parent) : Component(parent)
{
	Sprites.insert(this);
}

void Sprite::SetTexture(Texture* texture)
{
	this->texture = texture;
}

Texture* Sprite::GetTexture() const
{
	return texture;
}

void Sprite::OnDraw()
{
  if (texture != nullptr)
  {
    Effect->Use();
		Effect->Set("sprite", *texture);

		Matrix m = GetParent()->GetWorldMatrix();
		Matrix mvp = Camera::GetProjection() * Camera::GetView() * m;

    Effect->Set("mvp", mvp);
		Effect->Set("m", m);

    Quad->Use();

    Camera::Draw(DRAW_MODE_TRIANGLES, false, 6);
  }
}

Type Sprite::GetType()
{
  return typeid(Sprite);
}

void Sprite::OnDestroy()
{
	Sprites.erase(this);
}

void Sprite::Initialize()
{
  Shader* vs = new Shader(SHADER_TYPE_VERTEX, Asset("Shaders/Sprite/Shader.vs").GetText());

  if (!vs->IsValid())
  {
    PERROR("ERROR_SPRITE_VERTEX_SHADER: \n", vs->GetLog().c_str());
    throw;
  }

  Shader* fs = new Shader(SHADER_TYPE_FRAGMENT, Asset("Shaders/Sprite/Shader.fs").GetText());

  if (!fs->IsValid())
  {
    PERROR("ERROR_SPRITE_FRAGMENT_SHADER: \n", fs->GetLog().c_str());
    throw;
  }

	Effect = Managed<Core::Effect>(new Core::Effect({ vs, fs }));

  if (!Effect->IsValid())
  {
    PERROR("ERROR_SPRITE_EFFECT: \n", Effect->GetLog().c_str());
    throw;
  }

  Vector2 vertices[] =
  {
      Vector2(-0.5f,  0.5f),
      Vector2( 0.5f,  0.5f),
      Vector2(-0.5f, -0.5f),

      Vector2(-0.5f, -0.5f),
      Vector2( 0.5f,  0.5f),
      Vector2( 0.5f, -0.5f)
  };

  Vector2 uvs[] =
  {
      Vector2(0.0f, 1.0f),
      Vector2(1.0f, 1.0f),
      Vector2(0.0f, 0.0f),

      Vector2(0.0f, 0.0f),
      Vector2(1.0f, 1.0f),
      Vector2(1.0f, 0.0f)
  };

	Quad = std::make_unique<Mesh>();
	Quad->CreateBuffer(BUFFER_TARGET_VERTICES, BUFFER_ELEMENT_VECTOR2).SetData(vertices, 6);
	Quad->CreateBuffer(BUFFER_TARGET_UVS, BUFFER_ELEMENT_VECTOR2).SetData(uvs, 6);
	
  if (!Quad->Upload())
  {
    PERROR("ERROR_CREATE_SPRITE_QUAD");
    throw;
  }

  SUCCESS("Sprite: OK");
}

void Sprite::Draw()
{
	for (Sprite* sprite : Sprites)
	{
		sprite->OnDraw();
	}
}
