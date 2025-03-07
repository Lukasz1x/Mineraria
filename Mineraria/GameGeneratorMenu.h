#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameSettings.h"
#include "GameManager.h"
#include "Writing.h"
#include <string>
#include "GameState.h"

class GameGeneratorMenu
{
private:
	shared_ptr<RenderWindow> window;
	shared_ptr<GameSettings> game_settings;
	RectangleShape background;
	Texture background_texture;
	RectangleShape text_box1, text_box2;
	bool wn=false, sn=false;
	void load();
public:


	GameGeneratorMenu(shared_ptr<RenderWindow> window, shared_ptr<GameSettings>game_settings);
	~GameGeneratorMenu() = default;

	GameState run();
};