#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>
#include <filesystem>
#include "GameSettings.h"
#include "Writing.h"
#include "World.h"
#include "GameState.h"


class Singleplayer
{
private:
	shared_ptr<RenderWindow> window;
	shared_ptr<GameSettings> game_settings;
	RectangleShape background;
	Texture background_texture;
	void load();
	Font font;
	vector<pair<string, string>> worlds_data;
	vector<tuple<RectangleShape, Text, Text>>worlds;
	int x0, y0;
public:


	Singleplayer(shared_ptr<RenderWindow> window, shared_ptr<GameSettings>game_settings);
	~Singleplayer() = default;

	GameState run(std::string& world_name);
};

