#include "Player.h"
#include "Common.h"
#include "Generator.h"

#include "Simplex/Noise.h"

Managed<Actor> Platform;
Managed<Actor> PlayerInstance;
Managed<Actor> Ball;
Managed<TextureArray> Tileset;
Managed<Actor> Background;

void CreatePlayer ()
{
	Texture* texture = Png::Import("Player.png");
	texture->SetWrapping(TEXTURE_WRAPPING_MIRRORED_REPEAT);

	PlayerInstance = std::make_unique<Actor>();
	PlayerInstance->position = Vector3(0, 5, 0);
	PlayerInstance->scale = Vector3(5, 5, 5);

	Sprite* sprite = PlayerInstance->AddComponent<Sprite>();
	sprite->SetTexture(texture);

	Body* body = PlayerInstance->AddComponent<Body>();
	body->SetMovementType(MOVEMENT_TYPE_DYNAMIC);

	Circle* circle = PlayerInstance->AddComponent<Circle>();
	circle->SetRadius(1.5f);
	circle->SetDensity(20);
	circle->SetFriction(1.0f);
	circle->SetRestitution(0.0f);
	circle->Apply();

	PlayerInstance->AddComponent<Player>();
}

void CreateBackground()
{
	Background = std::make_unique<Actor>();

	Texture* grass	= Png::Import("Grass.png");
	Texture* dirt		= Png::Import("Dirt.png");
	Texture* sand		= Png::Import("Sand.png");
	Texture* rock		= Png::Import("Rock.png");
	Texture* dbg		= Png::Import("DirtBackground.png");
	Texture* rbg		= Png::Import("RockBackground.png");
	Texture* gur		= Png::Import("GrassUpRight.png");
	Texture* gul		= Png::Import("GrassUpLeft.png");

	Tileset = std::make_unique<TextureArray>(grass->GetFormat(), grass->GetWidth(), grass->GetHeight(), 8);
	Tileset->Set(0, *grass);
	Tileset->Set(1, *dirt);
	Tileset->Set(2, *sand);
	Tileset->Set(3, *rock);
	Tileset->Set(4, *dbg);
	Tileset->Set(5, *rbg);
	Tileset->Set(6, *gur);
	Tileset->Set(7, *gul);
	Tileset->SetSmoothing(true);
	Tileset->SetWrappingX(TEXTURE_WRAPPING_MIRRORED_REPEAT);
	Tileset->SetWrappingY(TEXTURE_WRAPPING_MIRRORED_REPEAT);

	Tilemap* tilemap = Background->AddComponent<Tilemap>();
	tilemap->SetQuadrantExtent(256);
	tilemap->SetTileset(Tileset.get());

	GeneratorConfiguration configuration = {};

	configuration.Terrain.TerraneanTiles		= Range<int>(0, 0);
	configuration.Terrain.SubterraneanTiles = Range<int>(1, 1);
	configuration.Terrain.UnderwaterTiles		= Range<int>(2, 2);
	configuration.Terrain.UndergroundTiles	= Range<int>(3, 3);

	configuration.TerrainDepth = 30;
	configuration.TerrainHillHeight = 30;
	configuration.TerrainHillRoughness = 1.33f;
	configuration.TerrainSeed = 9012;

	configuration.Tilemap = tilemap;
	configuration.Tileset = Tileset.get();

	configuration.UndergroundDepth = 1000;
	configuration.UndergroundSeed = -12842;
	configuration.UndergroundSpacePercentage = 0.2f;

	configuration.WorldExtent = 500;
	configuration.WorldScale = 1.00f;
	configuration.UndergroundScale = 2.00f;

	Generator::Generate(&configuration);
}

void Altra_Begin()
{
	CreateBackground();
	CreatePlayer();
}

void Altra_Tick (float dt)
{
	Camera::Begin();
	Camera::Clear(Vector4(0x87, 0xCE, 0xEB, 0xFF) * (1.0f / 255.0f), CLEAR_BOTH);

	PlayerInstance->OnTick();
	Background->OnTick();

	Sprite::Draw();
	Camera::End();
}
