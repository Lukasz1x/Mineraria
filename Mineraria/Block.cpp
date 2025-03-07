#include "Block.h"

Block::Block()
{
	ID = 0;
	//select();
}

void Block::setBlock(int x, int y, short Id)
{
	ID = Id;
	if (ID == 0)
	{
		block.setFillColor(sf::Color(255, 255, 255, 0)); // R, G, B, A
	}
	block.setSize(Vector2f(16, 16));
	block.setPosition(Vector2f(16.0f*x, 16.0f*y));
}

void Block::breakBlock()
{
	ID = 0;
	block.setFillColor(sf::Color(255, 255, 255, 0)); // R, G, B, A
}

void Block::draw(RenderTarget& target, RenderStates state) const
{
	if (ID != 0 || block.getOutlineThickness() != 0)
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

void Block::select()
{
	//if (&block != nullptr)
	//{
		block.setOutlineThickness(-1);
     	block.setOutlineColor(Color(255, 0, 0));
	//}
	//else
	//{
	//	std::cerr << "Error: Block object is null." << std::endl;
	//}

}

void Block::unselect()
{
	block.setOutlineThickness(0);
}