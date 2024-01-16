#include "Inventory.h"

Inventory::Inventory()
{
	healthbar.setPosition(1060,20);
	healthbar.setSize(Vector2f(204, 24));
	healthbar.setFillColor(Color(255, 0, 0));
	healthbar2.setPosition(1060, 20);
	healthbar2.setSize(Vector2f(204, 24));
	healthbar2.setFillColor(Color(255,255,255));
	healthbar2.setOutlineThickness(2);
	healthbar2.setOutlineColor(Color(0, 0, 0));
}

void Inventory::updateHealthbar(float h, float m)
{
	if (h < 0)
		h = 0;
	healthbar.setSize(Vector2f((float)(h / m) * 204, 24));
	std::cout << h<<" "<<m<<" " << (float)(h / m) * 204 << std::endl;
}

void Inventory::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->healthbar2);
	target.draw(this->healthbar);
}