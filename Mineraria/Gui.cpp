#include "Gui.h"

Gui::Gui(GameSettings* gs)
{
	game_settings = gs;
	healthbar.setPosition(1060,20);
	healthbar.setSize(Vector2f(204, 24));
	healthbar.setFillColor(Color(255, 0, 0));
	healthbar2.setPosition(1060, 20);
	healthbar2.setSize(Vector2f(204, 24));
	healthbar2.setFillColor(Color(255,255,255));
	healthbar2.setOutlineThickness(2);
	healthbar2.setOutlineColor(Color(0, 0, 0));
	font.loadFromFile("assets/fonts/andyb.ttf");
	health_text = new Writing("0/0", font, 1060+102, 24, 25);
	health_text->setColor(Color(0,0,0));
	deduwa_texture.loadFromFile("assets/deduwa.png");
	deduwa.setSize(Vector2f(game_settings->getWindowWidth(), game_settings->getWindowHeight()));
	deduwa.setTexture(&deduwa_texture);
	deduwa.setPosition(0, 0);
	respawn = new Writing("Respawn", font, game_settings->getWindowWidth() / 2, 0.65 * game_settings->getWindowHeight(), 0.08 * game_settings->getWindowHeight());
	main_menu = new Writing("Main Menu", font, game_settings->getWindowWidth() / 2, 0.75 * game_settings->getWindowHeight(), 0.08 * game_settings->getWindowHeight());
	if (respawn && main_menu) {
		respawn->setOutline(Color(0, 0, 0), 0.01 * game_settings->getWindowHeight());
		main_menu->setOutline(Color(0, 0, 0), 0.01 * game_settings->getWindowHeight());
		game_settings->gui_main_menu = main_menu;
		game_settings->gui_respawn = respawn;
	}
	else {
		// Handle the case where pointers are null
		std::cerr << "Error: Failed to initialize respawn or main_menu pointers!" << std::endl;
	}
}


void Gui::updateHealthbar(float h, float m)
{
	if (h < 0)
	{
		h = 0;
	}
		
	healthbar.setSize(Vector2f((float)(h / m) * 204, 24));
	health_text->setString(std::to_string(static_cast<int>(h)) + "/" + std::to_string(static_cast<int>(m)));
}

void Gui::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->healthbar2);
	target.draw(this->healthbar);
	target.draw(*health_text);
	if (game_settings->dead)
	{
		target.draw(deduwa);
		target.draw(*respawn);
		target.draw(*main_menu);
	}
		
}