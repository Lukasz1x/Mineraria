#include "Player.h"

Player::Player()
{
	entity.setPosition(0, 1750);
	entity.setSize((Vector2f(13.0f, 22.0f)));
	entity_texture.loadFromFile("assets/steve.png");
	entity.setTexture(&entity_texture);
	entity.setOrigin(Vector2f(7, 11));
}

Vector2f Player::getCenter()
{
	return entity.getPosition();
}

void Player::move_left()
{
	entity.setPosition(entity.getPosition() + Vector2f(-10, 0));
}

void Player::move_right()
{
	entity.setPosition(entity.getPosition() + Vector2f(10, 0));
}
