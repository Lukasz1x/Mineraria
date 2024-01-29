#pragma once

#include "Entity.h";
#include "Gui.h"
#include "GameSettings.h"

class Player : public Entity
{
private:
	Gui* gui;
	GameSettings* game_settings;


public:
	Player(GameSettings* gs);
	~Player() = default;
	void respawn();
	Vector2f getCenter();
	Gui draw_gui();
	void update();
	
};

