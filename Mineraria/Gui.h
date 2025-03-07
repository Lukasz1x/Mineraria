#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Writing.h"
#include "GameSettings.h"

using namespace sf;

class Gui : public sf::Drawable
{
private:
	RectangleShape healthbar, healthbar2;
	Font font;
	Writing* health_text, * respawn, * main_menu;
	RectangleShape deduwa;
	Texture deduwa_texture;
	shared_ptr<GameSettings> game_settings;
public:
	Gui(shared_ptr<GameSettings> game_settings);
	~Gui() = default;
	void updateHealthbar(float h, float m);
	void draw(RenderTarget& target, RenderStates state) const override;

};

