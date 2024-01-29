#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameSettings.h"
#include "GameManager.h"
#include "Writing.h"
#include <string>

class GameGeneratorMenu
{
private:
	RenderWindow& window;
	GameSettings* game_settings;
	RectangleShape background;
	Texture background_texture;
	RectangleShape text_box1, text_box2;
	bool wn=false, sn=false;
	void load();
public:


	GameGeneratorMenu(RenderWindow& window, GameSettings* game_settings);
	~GameGeneratorMenu() = default;

	int run();
};