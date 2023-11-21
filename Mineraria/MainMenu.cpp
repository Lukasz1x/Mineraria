#include "MainMenu.h"

MainMenu::MainMenu(RenderWindow& window, GameSettings& game_settings) : window(window), game_settings(game_settings) {}

void MainMenu::load()
{
	background_texture.loadFromFile("assets/background.png");
	background.setSize(Vector2f(game_settings.getWindowWidth(), game_settings.getWindowHeight()));
	background.setTexture(&background_texture);
	background.setPosition(0, 0);
}

int MainMenu::run()
{
	load();
	vector<Writing>texts;
	Font font_logo;
	Font font;
	font_logo.loadFromFile("assets/fonts/MinecraftTen.ttf");
	font.loadFromFile("assets/fonts/andyb.ttf");
	texts.emplace_back("Mineraria", font_logo, game_settings.getWindowWidth() / 2, 0.15 * game_settings.getWindowHeight(), 0.15 * game_settings.getWindowHeight());
	texts[0].setOutline(Color(0, 0, 0), 0.02 * game_settings.getWindowHeight());
	texts.emplace_back("Singleplayer", font, game_settings.getWindowWidth() / 2, 0.35 * game_settings.getWindowHeight(), 0.08 * game_settings.getWindowHeight());
	texts.emplace_back("Multiplayer", font, game_settings.getWindowWidth() / 2, 0.45 * game_settings.getWindowHeight(), 0.08 * game_settings.getWindowHeight());
	texts.emplace_back("Achivements", font, game_settings.getWindowWidth() / 2, 0.55 * game_settings.getWindowHeight(), 0.08 * game_settings.getWindowHeight());
	texts.emplace_back("Settings", font, game_settings.getWindowWidth() / 2, 0.65 * game_settings.getWindowHeight(), 0.08 * game_settings.getWindowHeight());
	texts.emplace_back("Quit Game", font, game_settings.getWindowWidth() / 2, 0.75 * game_settings.getWindowHeight(), 0.08 * game_settings.getWindowHeight());
	for (int i = 1; i < 6; i++)
	{
		texts[i].setOutline(Color(0, 0, 0), 0.01 * game_settings.getWindowHeight());
	}
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if ((event.type == Event::MouseButtonPressed) && (event.mouseButton.button == Mouse::Left))
			{
				for (int i = 1; i < 6; i++)
				{
					FloatRect textBounds = texts[i].getGlobalBounds();
					if (textBounds.contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
					{
						if (i == 5)
							window.close();
						return i+1;
					}
				}
			}
		}

		for (int i = 1; i < 6; i++)
		{
			FloatRect textBounds = texts[i].getGlobalBounds();
			if (textBounds.contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
			{
				texts[i].setOutline(Color(155, 155, 100));
				texts[i].setCharacterSize(1.1 * 0.08 * game_settings.getWindowHeight());
			}
			else
			{
				texts[i].setOutline(Color(0, 0, 0));
				texts[i].setCharacterSize(0.08 * game_settings.getWindowHeight());
			}
		}

		window.clear();
		window.draw(background);
		for (auto& text : texts)
		{
			window.draw(text);
		}
		window.display();
	}
}