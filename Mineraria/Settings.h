#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameSettings.h"
#include "GameManager.h"
#include "Writing.h"
#include "GameState.h"

class Settings
{
private:
	shared_ptr<RenderWindow> window;
	shared_ptr<GameSettings> game_settings;
	RectangleShape background;
	Texture background_texture;
	void load();
public:


	Settings(shared_ptr<RenderWindow> window, shared_ptr<GameSettings>game_settings);
	~Settings() = default;

	GameState run();
};

