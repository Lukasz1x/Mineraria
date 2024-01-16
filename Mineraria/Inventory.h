#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Inventory : public sf::Drawable
{
private:
	RectangleShape healthbar, healthbar2;
public:
	Inventory();
	~Inventory() = default;
	void updateHealthbar(float h, float m);
	void draw(RenderTarget& target, RenderStates state) const override;

};

