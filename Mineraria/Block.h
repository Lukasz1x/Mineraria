#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Block : public Drawable
{
private:
	short ID;
	RectangleShape block;
	void draw(RenderTarget& target, RenderStates state) const override;
	int hardness;
public:
	Block();
	~Block() = default;

	void setBlock(int x, int y, short Id);
	void setTextture(Texture& texture);
	short getBlockID();
	void select();
	void unselect();
	void breakBlock();
};

