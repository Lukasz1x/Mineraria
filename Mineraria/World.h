#pragma once

#include <fstream>
#include <vector>
#include <filesystem>
#include "Chunk.h"
#include "WorldGenerator.h"
#include <iostream>

using namespace std;


class World
{
private:
	vector<Chunk>chunks;
	string world_name;
	int seed;
public:
	World(string name, int seed);
	~World() = default;
	void save(Chunk& ch);
	void load();
	void unload();
	vector<Chunk>& getChunks();
};

