#include "Generator.h"
#include "Player.h"
#include "Common.h"

#include "Simplex/Noise.h"
#include "Random.h"

#include <random>
#include <math.h>

#define MAGIC_FREQUENCY 0.015f
#define UNDERGROUND_FREQUENCY (MAGIC_FREQUENCY * Configuration->UndergroundScale)
#define TERRAIN_FREQUENCY (MAGIC_FREQUENCY * Configuration->WorldScale)

#define UNDERGROUND_SAMPLE(X, Y) ((SimplexNoise::noise(float(X) * UNDERGROUND_FREQUENCY, float(Y) * UNDERGROUND_FREQUENCY, float(Configuration->UndergroundSeed)) + 1) / 2.0f)
#define TERRAIN_SAMPLE(X) SimplexNoise::noise(float(X) * TERRAIN_FREQUENCY, 0.0f, float(Configuration->TerrainSeed))

GeneratorConfiguration* Generator::Configuration;
Tilemap* Generator::Tilemap;
Bounds<int> Generator::Bounds;

void Generator::CreateUnderground()
{
	float sample, f;

	for (int y = (int)Configuration->TerrainHillHeight; y >= -Configuration->UndergroundDepth; y--)
	{
		for (int x = -Configuration->WorldExtent; x <= Configuration->WorldExtent; x++)
		{
			f = Configuration->UndergroundScale * MAGIC_FREQUENCY;
			sample = (SimplexNoise::noise(x * f, y * f) + 1) / 2.0f;

			if (sample <= Configuration->UndergroundSpacePercentage)
			{
				Tilemap->SetTile(x, y, -1);
			}
		}
	}
}

float GetBrightness(float b, float d)
{
	return b / (4.0f * 3.14159265359f * d * d);
}

bool Generator::Foton (int& x, int& y, int i, int j, float L)
{
	// Foton flying through the air
	while (Tilemap->GetTile(x, y) == -1)
	{
		Tilemap->SetTileLighting(x, y, L);

		x += i;
		y += j;

		if (!Bounds.Inside(x, y)) return false;
	}

	// Save the hit position
	int hx = x;
	int hy = y;

	// Smooth the block
	Smooth(hx, hy);

	float d;
	float b;

	do
	{
		// Distance from the surface
		d = (ABS(hx - x) + ABS(hy - y) + 1) * 0.2f;
		b = GetBrightness(L, d);

		if (b > Tilemap->GetTileLighting(x, y))
		{
			Tilemap->SetTileLighting(x, y, b);
		}

		x += i;
		y += j;

		if (!Bounds.Inside(x, y)) return false;

	} while (Tilemap->GetTile(x, y) != -1);

	return true;
}

void Generator::Smooth(int x, int y)
{
	if (Tilemap->GetTile(x, y) == 0 && Tilemap->GetTile(x, y + 1) == -1)
	{
		bool a = Tilemap->GetTile(x + 1, y) == -1;
		bool b = Tilemap->GetTile(x - 1, y) == -1;

		if (a && !b)
		{
			Tilemap->SetTile(x, y, 6);
		}
		else if (!a && b)
		{
			Tilemap->SetTile(x, y, 7);
		}
	}
}

void Generator::CreateSurfaces()
{
	int x, y;

	// Down
	for (x = Bounds.GetLeft(); x <= Bounds.GetRight(); x++)
	{
		y = Bounds.GetTop();

		while (Foton(x, y, 0, -1, 0.6f));
	}

	// Up
	for (x = Bounds.GetLeft(); x <= Bounds.GetRight(); x++)
	{
		y = Bounds.GetBottom();

		while (Foton(x, y, 0, 1, 0.6f));
	}

	// Right
	for (y = Bounds.GetBottom(); y <= Bounds.GetTop(); y++)
	{
		x = Bounds.GetLeft();

		while (Foton(x, y, 1, 0, 0.6f));
	}

	// Left
	for (y = Bounds.GetBottom(); y <= Bounds.GetTop(); y++)
	{
		x = Bounds.GetRight();

		while (Foton(x, y, -1, 0, 0.6f));
	}
}

void Generator::CreateTerrain()
{
	TerrainBiome& biome = Configuration->Terrain;
	Random<> random(Configuration->TerrainSeed);

	for (int x = -Configuration->WorldExtent; x <= Configuration->WorldExtent; x++)
	{
		float sample = (float)TERRAIN_SAMPLE(x);
		float sign   = (float)SIGN(sample);

		sample = POW(ABS(sample), Configuration->TerrainHillRoughness) * sign;

		int height = int(sample * Configuration->TerrainHillHeight);

		for (int y = -Configuration->UndergroundDepth; y < height; y++)
		{
			if (y == height - 1)
			{
				Tilemap->SetTile(x, y, biome.TerraneanTiles.GetValue(random()));

				Actor* hitbox = new Actor();
				hitbox->position = Vector3(x, y, 0) + Vector3(0.5f, 0.5f, 0);

				Body* body = hitbox->AddComponent<Body>();
				body->SetMovementType(MOVEMENT_TYPE_STATIC);

				Box* box = hitbox->AddComponent<Box>();
				box->SetExtent(Vector2(0.5f));
				box->Apply();
			}
			else if (height - y <= Configuration->TerrainDepth)
			{
				Tilemap->SetTile(x, y, biome.SubterraneanTiles.GetValue(random()));
			}
			else
			{
				Tilemap->SetTile(x, y, biome.UndergroundTiles.GetValue(random()));
			}
		}
	}
}

void Generator::Generate(GeneratorConfiguration* configuration)
{
	Configuration = configuration;
	Tilemap = Configuration->Tilemap;

	Bounds = ::Bounds<int>(-Configuration->WorldExtent,
													(int)Configuration->TerrainHillHeight,
													Configuration->WorldExtent,
												 -Configuration->UndergroundDepth);
	CreateTerrain();
	CreateUnderground();
	CreateSurfaces();

	Tilemap->Apply();
}

void Surface::Add(SurfaceNormal& normal)
{
	Normals.push_back(normal);
}

bool Surface::Continue(SurfaceNormal& normal, Chain& chain)
{
	/*List<SurfaceNormal&> normals;

	for (SurfaceNormal& i : Normals)
	{
		if (i.Direction * normal.Direction >= 0)
		{
			normals.push_back(i);
		}
	}

	std::sort(normals.begin(), normals.end(), [normal](const SurfaceNormal& a, const SurfaceNormal& b) -> bool
	{
		return (a.Position - normal.Position).GetSquareMagnitude() < (b.Position - normal.Position).GetSquareMagnitude();
	});

	for (SurfaceNormal& i : normals)
	{
		chain.Continue()
	}*/

	return false;
}
