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
public:
	Block() = default;
	~Block() = default;

	void setBlock(int x, int y, short Id=0);
	short getBlockID();
};

