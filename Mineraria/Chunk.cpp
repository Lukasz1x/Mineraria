#include "Chunk.h"

Chunk::Chunk(int position_x, int seed)
{
	x = position_x;
	this->seed = seed;
}

void Chunk::setBlock(int x, int y, short ID)
{
	int tab_x = x - 32 * this->x;
	blocks[tab_x][y].setBlock(x, y, ID);
}

short Chunk::getBlockID(int x, int y)
{
	int tab_x = x - 32 * this->x;
	return blocks[tab_x][y].getBlockID();
}

short Chunk::getBlockID_PX(int x, int y)
{
	return blocks[x][y].getBlockID();
}


short Chunk::getChunkX()
{
	return x;  //xd ?
}

int Chunk::getSeed()
{
	return seed;
}

Block& Chunk::block(int x, int y)
{
	return blocks[x][y];
}

void Chunk::selectBlock(int x, int y)
{
	blocks[x][y].select();
}

void Chunk::unselectBlock(int x, int y)
{
	blocks[x][y].unselect();
}

void Chunk::breakBlock(int x, int y)
{
	blocks[x][y].breakBlock();
}
