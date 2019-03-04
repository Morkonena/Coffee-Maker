//
// Created by Mörkönenä on 9.8.2018
//

#ifndef CORE_TILEMAP_H
#define CORE_TILEMAP_H

#include <Component.h>
#include <Effect.h>
#include <Mesh.h>
#include <Standard.h>
#include <Texture.h>
#include <TextureArray.h>
#include <Vector2.h>

namespace Core
{
  class Tilemap;

	enum Space
	{
		SPACE_LOCAL,
		SPACE_WORLD
	};

  class Quadrant
  {
  private:
		static Managed<Effect> Effect;
		static Managed<Mesh> Quad;

		friend class Tilemap;
		static void Initialize();

		static int Extent;

	private:
    Tilemap* Map;

    Texture Tilemap;
		Texture Lightmap;

		int Wx, Wy;
		int Qx, Qy;

		bool Dirty = false;

	public:
		bool operator==(const Quadrant& rhs) const;

  public:
    Quadrant(Core::Tilemap* tilemap, int x, int y);

    void Draw ();

    void SetTile(int x, int y, uint tile, Space space = SPACE_LOCAL);
    uint GetTile(int x, int y, Space space = SPACE_LOCAL) const;

		void	SetTileLighting(int x, int y, float lighting, Space space = SPACE_LOCAL);
		float GetTileLighting(int x, int y, Space space = SPACE_LOCAL) const;

		void Apply ();
		
		Vector2 GetQuadrantPosition() const;
    Vector2 GetWorldPosition() const;

    int GetExtent() const;

		bool IsEmpty() const;
  };

  class Tilemap : public Component
  {
	private:
		TextureArray* Tileset;

		float TileExtent = 1.0f;
    
    mutable List<Quadrant> Quadrants;

	private:
    void GetQuadrantPosition(int x, int y, int& ix, int& iy) const;

	public:
		static inline void Initialize()
		{
			Quadrant::Initialize();
		}

  public:
		using Component::Component;

    void						SetTileset (TextureArray* tileset);
    TextureArray*		GetTileset () const;

    Quadrant&		GetQuadrantAt (Vector2 position) const;
		Quadrant&		GetQuadrantAt (int x, int y) const;

    Quadrant&		GetQuadrant (int ix, int iy) const;

		void Remove(Quadrant& quadrant);

		void SetTile(Vector2 position, int tile);
    void SetTile(int x, int y, int tile);

		int	GetTile(Vector2 position) const;
    int GetTile(int x, int y) const;

		void	SetTileLighting(int x, int y, float lighting);
		float	GetTileLighting(int x, int y) const;

		void Apply();

		void	SetQuadrantExtent(int size);
		int		GetQuadrantExtent() const;

    void  SetTileExtent(float size);
    float GetTileExtent() const;

    virtual void OnTick() override;

		virtual Type GetType() override;
  };
}

#endif // !CORE_TILEMAP_H

