#pragma once

#include "Entity.h";
#include "Gui.h"
#include "GameSettings.h"

class Player : public Entity
{
private:
	Gui* gui;
	shared_ptr<GameSettings> game_settings;
	Vector2f spawn_point;


public:
	Player(shared_ptr<GameSettings> game_settings);
	~Player() = default;
	void respawn();
	Vector2f getCenter();
	void setSpawnPoint(Vector2f spawn_point);
	Gui draw_gui();
	void update();
	void setPosition(Vector2f pos);
	
};

