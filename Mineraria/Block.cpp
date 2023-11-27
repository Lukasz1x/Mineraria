#include "Block.h"

Block::Block()
{
	ID = 0;
}

void Block::setBlock(int x, int y, short Id)
{
	ID = Id;
	block.setSize(Vector2f(16, 16));
	block.setPosition(Vector2f(16.0f*x, 16.0f*y));
}

void Block::draw(RenderTarget& target, RenderStates state) const
{
	if(ID!=0)
		target.draw(this->block);
}

short Block::getBlockID()
{
	return ID;
}

void Block::setTextture(Texture& texture)
{
	block.setTexture(&texture);
}