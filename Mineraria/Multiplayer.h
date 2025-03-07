#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameSettings.h"
#include "GameManager.h"
#include "Writing.h"
#include "GameState.h"

class Multiplayer
{
private:
	shared_ptr<RenderWindow> window;
	shared_ptr<GameSettings> game_settings;
	RectangleShape background;
	Texture background_texture;
	void load();
public:


	Multiplayer(shared_ptr<RenderWindow> window, shared_ptr<GameSettings>game_settings);
	~Multiplayer() = default;

	GameState run(std::string& world_name);
};

