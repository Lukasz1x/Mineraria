#pragma once

#include <fstream>
#include <vector>
#include <filesystem>
#include "Chunk.h"
#include "WorldGenerator.h"
#include "BlockTexture.h"
#include <thread>
#include <iostream>

using namespace std;


class World
{
private:
	vector<Chunk>chunks;
	vector<BlockTexture> textures;
	string world_name;
	int seed;
	WorldGenerator generator;
	Vector2f spawn_point=Vector2f(0,0);
public:
	World(string name, int seed, string seed_hash);
	~World() = default;
	void generate(Chunk& ch);
	void save(Chunk& ch);
	void load(int chunk_x);
	void unload(int chunk_x);
	void setTextures(Chunk& ch);
	void createNewWorld();
	void selectBlock(int x, int y);
	void unselectBlock(int x, int y);
	short getBlockID(int x, int y);
	void breakBlock(int x, int y);
	Vector2f getSpawnPoint();
	vector<Chunk>& getChunks();
};

