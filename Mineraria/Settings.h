#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameSettings.h"
#include "GameManager.h"
#include "Writing.h"

class Settings
{
private:
	RenderWindow& window;
	GameSettings& game_settings;
	RectangleShape background;
	Texture background_texture;
	void load();
public:


	Settings(RenderWindow& window, GameSettings& game_settings);
	~Settings() = default;

	int run();
};

