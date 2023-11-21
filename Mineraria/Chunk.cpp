#include "Chunk.h"

Chunk::Chunk(int position_x)
{
	x = position_x;
}

void Chunk::setBlock(short ID, int x, int y)
{
	x = x - 32 * this->x;
	blocks[x][y].setBlock(ID, x, y);
}

short Chunk::getBlockID(int x, int y)
{
	x = x - 32 * this->x;
	return blocks[x][y].getBlockID();
}

short Chunk::getChunkX()
{
	return x;
}

Block& Chunk::block(int x, int y)
{
	return blocks[x][y];
}