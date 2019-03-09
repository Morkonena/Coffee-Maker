//
// Created by Mörkönenä on 1.1.2019
//

#ifndef WORLD_H
#define WORLD_H

#include "Common.h"

class World
{
private:
	static Managed<Actor> Instance;
	static Managed<Tilemap> Tilemap;

public:
	static void Initialize ();
	static void Set (int x, int y, int tile);
};

#endif // !WORLD_H
