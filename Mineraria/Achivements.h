#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameSettings.h"
#include "GameManager.h"
#include "Writing.h"
#include "GameState.h"

class Achivements
{
private:
	shared_ptr<RenderWindow> window;
	shared_ptr<GameSettings> game_settings;
	RectangleShape background;
	Texture background_texture;
	void load();
public:


	Achivements(shared_ptr<RenderWindow> window, shared_ptr<GameSettings>game_settings);
	~Achivements() = default;

	GameState run();
};

