#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameSettings.h"
#include "GameManager.h"
#include "Writing.h"

class Multiplayer
{
private:
	RenderWindow& window;
	GameSettings* game_settings;
	RectangleShape background;
	Texture background_texture;
	void load();
public:


	Multiplayer(RenderWindow& window, GameSettings* game_settings);
	~Multiplayer() = default;

	int run(std::string& world_name);
};

