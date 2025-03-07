#include "Player.h"

Player::Player(shared_ptr<GameSettings> game_settings) : game_settings(game_settings)
{
	entity.setSize((Vector2f(13.0f, 22.0f)));
	entity_texture.loadFromFile("assets/steve.png");
	entity.setTexture(&entity_texture);
	gui = new Gui(game_settings);
	health = 100;
	max_health = 100;
	game_settings->dead = false;

}

Vector2f Player::getCenter()
{
	return entity.getPosition()+ Vector2f(7, 11);
}

Gui Player::draw_gui()
{
	return *gui;
}

void Player::update()
{
	if ((health < max_health) && (health > 0))
	{
		health += (max_health / 40) / 60;
		if (health > max_health)
			health = max_health;
	}
	if (health <= 0)
	{
		game_settings->dead = true;
		this->setVelocity(Vector2f(0, 0));
	}
		
	gui->updateHealthbar(health, max_health);
	
}

void Player::respawn()
{
	entity.setPosition(spawn_point.x, spawn_point.y-22);
	health = max_health;
	game_settings->dead = false;
}

void Player::setSpawnPoint(Vector2f spawn_point)
{
	this->spawn_point = spawn_point;
}

void Player::setPosition(Vector2f pos)
{
	entity.setPosition(Vector2f(pos.x, pos.y-22));
}