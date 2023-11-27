#pragma once

#include "FastNoiseLite.h"
#include "Chunk.h"
#include <iostream>

class WorldGenerator
{
private:
	const int chunkSizeX = 32;
	const int chunkSizeY = 320;
	const int groundLevel = 120;
public:
	WorldGenerator();
	~WorldGenerator() = default;
	void generate(Chunk& ch);
};

