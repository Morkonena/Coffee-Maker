//
// Created by Mörkönenä on 14.8.2018
//

#ifndef CORE_SPRITE_H
#define CORE_SPRITE_H

#include <Component.h>
#include <Effect.h>
#include <Mesh.h>
#include <Standard.h>
#include <Texture.h>

namespace Core
{
  class Sprite : public Component
  {
  private:
		static Managed<Effect> Effect;
		static Managed<Mesh> Quad;

		static Set<Sprite*> Sprites;

	private:
		Texture* texture;

	private:
		void OnDraw();

	public:
		static void Initialize();
		static void Draw();

  public:
		Sprite(Actor* parent);

		void			SetTexture (Texture* texture);
		Texture*	GetTexture () const;

    virtual Type GetType() override;

		virtual void OnDestroy() override;
  };
}

#endif // !CORE_SPRITE_H


