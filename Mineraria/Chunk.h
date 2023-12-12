#pragma once

#include "Block.h"

class Chunk
{
private:
	int x;
	int seed;
public:
	Block blocks[32][320];
	Chunk(int position_x, int seed);
	~Chunk() = default;
	void setBlock(int x, int y, short ID);
	short getBlockID(int x, int y);
	short getBlockID_PX(int x, int y);
	void selectBlock(int x, int y);
	void unselectBlock(int x, int y);
	short getChunkX();
	int getSeed();
	void breakBlock(int x, int y);
	Block& block(int x, int y);
};

