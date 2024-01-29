#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameSettings.h"
#include "Writing.h"

using namespace sf;

class MainMenu
{
private:
	RenderWindow& window;
	GameSettings* game_settings;
	RectangleShape background;
	Texture background_texture;
	void load();
public:
	

	MainMenu(RenderWindow& window, GameSettings* game_settings);
	~MainMenu() = default;

	int run();

};

