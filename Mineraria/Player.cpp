#include "Player.h"

Player::Player()
{
	entity.setPosition(0, 1856-22); //do zmiany
	entity.setSize((Vector2f(13.0f, 22.0f)));
	entity_texture.loadFromFile("assets/steve.png");
	entity.setTexture(&entity_texture);
	inv = new Inventory;
	health = 100;
	max_health = 100;
	//entity.setOrigin(Vector2f(7, 11));
}

Vector2f Player::getCenter()
{
	return entity.getPosition()+ Vector2f(7, 11);
}

Inventory Player::draw_inv()
{
	return *inv;
}

void Player::update()
{
	inv->updateHealthbar(health, max_health);
}

