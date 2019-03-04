//
// Created by Mörkönenä on 16.2.2019
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include "Common.h"
#include "Range.h"
#include "Bounds.h"

struct TerrainBiome
{
	Range<int> TerraneanTiles;
	Range<int> SubterraneanTiles;
	Range<int> UnderwaterTiles;
	Range<int> UndergroundTiles;
};

struct GeneratorConfiguration
{
	float WorldScale = 1.0f;
	float UndergroundScale = 1.0f;
	int		WorldExtent;
	int		UndergroundDepth;
	float UndergroundSpacePercentage;
	float	TerrainHillHeight;
	float TerrainHillRoughness;
	int		TerrainDepth;

	TextureArray* Tileset;
	Tilemap*			Tilemap;

	TerrainBiome Terrain;

	int UndergroundSeed;
	int TerrainSeed;
};

class Chain
{

};

struct SurfaceNormal
{
	Vector2 Position;
	Vector2 Direction;
};

class Surface
{
private:
	List<SurfaceNormal> Normals;

public:
	void Add(SurfaceNormal& normal);
	bool Continue(SurfaceNormal& normal, Chain& chain);
};

class Generator
{
private:
	static GeneratorConfiguration* Configuration;
	static Tilemap* Tilemap;
	static Bounds<int> Bounds;

	static bool Foton(int& x, int& y, int i, int j, float b);
	static void Smooth(int x, int y);

	static void CreateTerrain();
	static void CreateUnderground();
	static void CreateSurfaces();

public:
	static void Generate(GeneratorConfiguration* configuration);
};

#endif // !GENERATOR_H