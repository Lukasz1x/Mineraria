#include "Block.h"

void Block::setBlock(int x, int y, short Id)
{
	std::cout << "Block ID: " << Id << " at position (" << x << ", " << y << ")\n";
	ID = Id;
	block.setSize(Vector2f(16, 16));
	block.setPosition(Vector2f(16*x, 16*y));
	if (ID == 0)
	{
		block.setFillColor(Color(0, 0, 255));
		block.setOutlineThickness(1);
	}
	else
	{
		block.setOutlineThickness(1);
		block.setFillColor(Color(126, 70, 70));
	}
	
}

void Block::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->block);
}

short Block::getBlockID()
{
	return ID;
}