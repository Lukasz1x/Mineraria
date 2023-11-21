#pragma once

#include "Block.h"

class Chunk
{
private:
	int x;
	Block blocks[32][320];
public:
	Chunk(int position_x);
	~Chunk() = default;
	void setBlock(short ID, int x, int y);
	short getBlockID(int x, int y);
	short getChunkX();
	Block& block(int x, int y);
};

