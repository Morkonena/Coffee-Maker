#include "Sprite.h"
#include "Tilemap.h"

#include <Actor.h>
#include <Asset.h>
#include <Camera.h>
#include <Log.h>

#include <cmath>

using namespace Core;

Managed<Effect> Quadrant::Effect;
Managed<Mesh> Quadrant::Quad;

int Quadrant::Extent;

#define FLOOR(X) floorf(X)

void Tilemap::GetQuadrantPosition(int x, int y, int& ix, int& iy) const
{
	ix = (int)FLOOR(x / (float)Quadrant::Extent);
	iy = (int)FLOOR(y / (float)Quadrant::Extent);
}

Quadrant& Tilemap::GetQuadrantAt(int x, int y) const
{
	int ix;
	int iy;

	GetQuadrantPosition(x, y, ix, iy);

  return GetQuadrant(ix, iy);
}

Quadrant& Tilemap::GetQuadrantAt(Vector2 position) const
{
	return GetQuadrantAt((int)position.x, (int)position.y);
}

Quadrant& Tilemap::GetQuadrant(int qx, int qy) const
{
  for (Quadrant& i : Quadrants)
  {
    if (i.Qx == qx && i.Qy == qy)
    {
      return i;
    }
  }

	Quadrant quadrant(const_cast<Tilemap*>(this), qx, qy);
  Quadrants.push_back(std::move(quadrant));

	return Quadrants.back();
}

void Tilemap::Remove(Quadrant& quadrant)
{
  Quadrants.erase(std::find(Quadrants.begin(), Quadrants.end(), quadrant));
}

void Tilemap::SetTileset(TextureArray* tileset)
{
  this->Tileset = tileset;
}

TextureArray* Tilemap::GetTileset() const
{
  return Tileset;
}

void Tilemap::SetTile(int x, int y, int tile)
{
	GetQuadrantAt(x, y).SetTile(x, y, (tile < 0 ? 0 : tile + 1), SPACE_WORLD);
}

void Tilemap::SetTile(Vector2 position, int tile)
{
	SetTile((int)position.x, (int)position.y, tile);
}

int Tilemap::GetTile(int x, int y) const
{
	return GetQuadrantAt(x, y).GetTile(x, y, SPACE_WORLD) - 1;
}

int Tilemap::GetTile(Vector2 position) const
{
	return GetTile((int)position.x, (int)position.y);
}

void Tilemap::SetTileLighting(int x, int y, float lighting)
{
	int qx, qy;
	int ix, iy;
	int iqx, iqy;

	GetQuadrantPosition(x, y, qx, qy);
	GetQuadrant(qx, qy).SetTileLighting(x, y, lighting, SPACE_WORLD);

	for (ix = -1; ix <= 1; ix++)
	{
		for (iy = -1; iy <= 1; iy++)
		{
			GetQuadrantPosition(x + ix, y + iy, iqx, iqy);

			if (iqx != qx || iqy != qy)
			{
				GetQuadrant(iqx, iqy).SetTileLighting(x, y, lighting, SPACE_WORLD);
			}
		}
	}
}

float Tilemap::GetTileLighting(int x, int y) const
{
	return GetQuadrantAt(Vector2(x, y)).GetTileLighting(x, y, SPACE_WORLD);
}

void Tilemap::Apply()
{
	for (Quadrant& i : Quadrants)
	{
		i.Apply();
	}
}

void Tilemap::SetQuadrantExtent(int extent)
{
	if (Quadrants.size() > 0)
	{
		PERROR("ERROR_TILEMAP_RUNNING: (Quadrant size can only be modified when tilemap doesn't hold any quadrants)");
		throw;
	}

	Quadrant::Extent = extent;
}

int Tilemap::GetQuadrantExtent() const
{
	return Quadrant::Extent;
}

void Tilemap::SetTileExtent(float extent)
{
	TileExtent = extent;
}

float Tilemap::GetTileExtent() const
{
	return TileExtent;
}

void Tilemap::OnTick()
{
  if (Tileset)
  {
    for (Quadrant& i : Quadrants)
    {
      i.Draw();
    }
  }
}

Type Tilemap::GetType()
{
  return typeid(Tilemap);
}





Quadrant::Quadrant(Core::Tilemap* tilemap, int x, int y) : 
	Map(tilemap), Qx(x), Qy(y), Wx(x * Extent), Wy(y * Extent)
{
	int le = 1 + Extent + 1;

	auto* tilemap_pixels = new uint[Extent * Extent];
	memset(tilemap_pixels, 0, Extent * Extent * sizeof(uint));

	auto* lightmap_pixels = new float[le * le];
	memset(lightmap_pixels, 0, le * le * sizeof(float));

  Tilemap.SetPixels(TEXTURE_FORMAT_INT, Extent, Extent, tilemap_pixels);
  Tilemap.SetSmoothing(false);

	Lightmap.SetPixels(TEXTURE_FORMAT_FLOAT, le, le, lightmap_pixels);
	Lightmap.SetSmoothing(false);
}

bool Quadrant::operator==(const Quadrant& rhs) const
{
	return Qx == rhs.Qx && Qy == rhs.Qy;
}

bool IsFull(void *memory, byte value, uint size)
{
	auto* pointer = static_cast<byte*>(memory);
  return (*pointer == value) && memcmp(pointer, pointer + 1, size - 1) == 0;
}

bool Quadrant::IsEmpty() const
{
  return IsFull(Tilemap.GetPixels(), 0, Tilemap.GetWidth() * Tilemap.GetHeight() * sizeof(int));
}

void Quadrant::SetTile(int x, int y, uint tile, Space space)
{
	uint* pixels = static_cast<uint*>(Tilemap.GetPixels());

	if (space == SPACE_WORLD)
	{
		pixels[(y - Wy) * Tilemap.GetWidth() + (x - Wx)] = tile;
	}
	else
	{
		pixels[y * Tilemap.GetWidth() + x] = tile;
	}

	Dirty = true;
}

uint Quadrant::GetTile(int x, int y, Space space) const
{
	uint* pixels = static_cast<uint*>(Tilemap.GetPixels());

	if (space == SPACE_WORLD)
	{
		return pixels[(y - Wy) * Tilemap.GetWidth() + (x - Wx)];
	}

  return pixels[y * Tilemap.GetWidth() + x];
}

void Quadrant::SetTileLighting(int x, int y, float lighting, Space space)
{
	float* pixels = static_cast<float*>(Lightmap.GetPixels());
	
	x++;
	y++;

	if (space == SPACE_WORLD)
	{
		pixels[(y - Wy) * Lightmap.GetWidth() + (x - Wx)] = lighting;
	}
	else
	{
		pixels[y * Lightmap.GetWidth() + x] = lighting;
	}

	Dirty = true;
}

float Quadrant::GetTileLighting(int x, int y, Space space) const
{
	float* pixels = static_cast<float*>(Lightmap.GetPixels());

	x++;
	y++;

	if (space == SPACE_WORLD)
	{
		return pixels[(y - Wy) * Lightmap.GetWidth() + (x - Wx)];
	}

	return pixels[y * Lightmap.GetWidth() + x];
}

void Quadrant::Apply()
{
	if (Dirty)
	{
		Tilemap.Apply();
		Lightmap.Apply();
		Dirty = false;
	}
}

void Quadrant::Draw()
{
  Effect->Use();
	Effect->Set("tilemap", Tilemap);
	Effect->Set("lightmap", Lightmap);
	Effect->Set("tileset", *Map->GetTileset());

	Matrix m = Map->GetParent()->GetWorldMatrix();
	Matrix mvp = Camera::GetProjection() * Camera::GetView() * m;

  Effect->Set("mvp", mvp);
  Effect->Set("position", Vector2(Wx, Wy));
  Effect->Set("extent", Tilemap.GetWidth());
  Effect->Set("scale", Map->GetTileExtent());

  Quad->Use();

  Camera::Draw(DRAW_MODE_TRIANGLES, false, 6);
}

Vector2 Quadrant::GetQuadrantPosition() const
{
	return Vector2(Qx, Qy);
}

Vector2 Quadrant::GetWorldPosition() const
{
	return Vector2(Wx, Wy);
}

int Quadrant::GetExtent() const
{
  return Extent;
}

void Quadrant::Initialize()
{
  Shader* vs = new Shader(SHADER_TYPE_VERTEX, Asset("Shaders/Tilemap/Shader.vs").GetText());

  if (!vs->IsValid())
  {
    PERROR("ERROR_TILEMAP_VERTEX_SHADER: \n", vs->GetLog().c_str());
    throw;
  }

  Shader* fs = new Shader(SHADER_TYPE_FRAGMENT, Asset("Shaders/Tilemap/Shader.fs").GetText());

  if (!fs->IsValid())
  {
		PERROR("ERROR_TILEMAP_FRAGMENT_SHADER: \n", fs->GetLog().c_str());
    throw;
  }

	Effect = Managed<Core::Effect>(new Core::Effect({ vs, fs }));

  if (!Effect->IsValid())
  {
		PERROR("ERROR_TILEMAP_EFFECT: \n%s", Effect->GetLog());
    throw;
  }
	
  Vector2 vertices[] =
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
	
  if (!Quad->Upload())
  {
    PERROR("ERROR_CREATE_TILEMAP_QUAD");
    throw;
  }

	Quadrant::Extent = 16;

	SUCCESS("Tilemap: OK");
}
