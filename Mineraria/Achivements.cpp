#include "Achivements.h"

Achivements::Achivements(RenderWindow& window, GameSettings* game_settings) : window(window), game_settings(game_settings) {}

void Achivements::load()
{
	background_texture.loadFromFile("assets/background.png");
	background.setSize(Vector2f(game_settings->getWindowWidth(), game_settings->getWindowHeight()));
	background.setTexture(&background_texture);
	background.setPosition(0, 0);
}

int Achivements::run()
{
	load();
	vector<Writing>texts;
	Font font;
	font.loadFromFile("assets/fonts/andyb.ttf");
	texts.emplace_back("Cooming Soon", font, game_settings->getWindowWidth() / 2, 0.08 * game_settings->getWindowHeight(), 0.1 * game_settings->getWindowHeight());
	texts.emplace_back("Cancel", font, 0.33 * game_settings->getWindowWidth(), 0.9 * game_settings->getWindowHeight(), 0.08 * game_settings->getWindowHeight());
	//texts.emplace_back("Create New World", font, 0.66 * game_settings->getWindowWidth(), 0.9 * game_settings->getWindowHeight(), 0.08 * game_settings->getWindowHeight());

	for (int i = 1; i < 2; i++)
	{
		texts[i].setOutline(Color(0, 0, 0), 0.01 * game_settings->getWindowHeight());
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
				for (int i = 1; i < 3; i++)
				{
					FloatRect textBounds = texts[i].getGlobalBounds();
					if (textBounds.contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
					{
						switch (i)
						{
						case 1:
						{

							return 1;
						}
						case 2:
						{

						}
						default:
							break;
						}
					}
				}
			}
		}

		for (int i = 1; i < 2; i++)
		{
			FloatRect textBounds = texts[i].getGlobalBounds();
			if (textBounds.contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
			{
				texts[i].setOutline(Color(155, 155, 100));
				texts[i].setCharacterSize(1.1 * 0.08 * game_settings->getWindowHeight());
			}
			else
			{
				texts[i].setOutline(Color(0, 0, 0));
				texts[i].setCharacterSize(0.08 * game_settings->getWindowHeight());
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