#ifndef COMMON_H
#define COMMON_H

#ifdef ANDROID

#include <cmath>
#define ABS(A)		abs((A))
#define POW(A, B) pow((A), (B))
#define SIGN(A)		((A) < 0 ? -1 : 1)

#include <Actor.h>
#include <Asset.h>
#include <Audio.h>
#include <AudioSystem.h>
#include <Body.h>
#include <Box.h>
#include <Camera.h>
#include <Console.h>
#include <Framebuffer.h>
#include <Hitbox.h>
#include <Input.h>
#include <Log.h>
#include <Physics.h>
#include <Sprite.h>
#include <Texture.h>
#include <Tilemap.h>
#include <Png.h>

using namespace Core;

#include "Time.h"

#else // WINDOWS & Linux

#include <cmath>
#define ABS(A)		abs((A))
#define POW(A, B) pow((A), (B))
#define SIGN(A)		((A) < 0 ? -1 : 1)

#include <Actor.h>
#include <Asset.h>
#include <Audio.h>
#include <AudioSystem.h>
#include <Body.h>
#include <Box.h>
#include <Camera.h>
#include <Console.h>
#include <Framebuffer.h>
#include <Graphics.h>
#include <Hitbox.h>
#include <Input.h>
#include <Log.h>
#include <Physics.h>
// #include <Pool.h> TODO: Linux Support
// #include <Screen.h> TODO: Linux Support
#include <Sprite.h>
#include <Texture.h>
#include <Tilemap.h>
#include <Window.h>
// #include <Windows.h>
#include <Png.h>

using namespace Core;

#include "Time.h"

#endif // ANDROID

#endif // !COMMON_H
