#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameSettings.h"
#include "Writing.h"
#include "GameState.h"

using namespace sf;

class MainMenu
{
private:
	shared_ptr<RenderWindow> window;
	shared_ptr<GameSettings> game_settings;
	RectangleShape background;
	Texture background_texture;
	void load();
public:
	

	MainMenu(shared_ptr<RenderWindow> window, shared_ptr<GameSettings>game_settings);
	~MainMenu() = default;

	GameState run();

};

