#include "GameGeneratorMenu.h"

GameGeneratorMenu::GameGeneratorMenu(RenderWindow& window, GameSettings* game_settings) : window(window), game_settings(game_settings) {}

void GameGeneratorMenu::load()
{
	background_texture.loadFromFile("assets/background.png");
	background.setSize(Vector2f(game_settings->getWindowWidth(), game_settings->getWindowHeight()));
	background.setTexture(&background_texture);
	background.setPosition(0, 0);
	text_box1.setSize(Vector2f(0.6 * game_settings->getWindowWidth(), 0.1 * game_settings->getWindowHeight()));
	text_box1.setOrigin(Vector2f(0.3 * game_settings->getWindowWidth(), 0.05 * game_settings->getWindowHeight()));
	text_box1.setPosition(0.5 * game_settings->getWindowWidth(), 0.3 * game_settings->getWindowHeight());
	text_box1.setOutlineColor(Color(255, 255, 255));
	text_box1.setOutlineThickness(-0.0075 * game_settings->getWindowHeight());
	text_box1.setFillColor(Color(0,0,0));
	text_box2.setSize(Vector2f(0.6 * game_settings->getWindowWidth(), 0.1 * game_settings->getWindowHeight()));
	text_box2.setOrigin(Vector2f(0.3 * game_settings->getWindowWidth(), 0.05 * game_settings->getWindowHeight()));
	text_box2.setPosition(0.5 * game_settings->getWindowWidth(), 0.55 * game_settings->getWindowHeight());
	text_box2.setOutlineColor(Color(255, 255, 255));
	text_box2.setOutlineThickness(-0.0075 * game_settings->getWindowHeight());	
	text_box2.setFillColor(Color(0,0,0));
}

int GameGeneratorMenu::run()
{
	load();
	vector<Writing>texts;
	Font font;
	font.loadFromFile("assets/fonts/andyb.ttf");
	texts.emplace_back("New World", font, game_settings->getWindowWidth() / 2, 0.275 * game_settings->getWindowHeight(), 0.065 * game_settings->getWindowHeight());
	texts.emplace_back("123", font, game_settings->getWindowWidth() / 2, 0.525 * game_settings->getWindowHeight(), 0.065 * game_settings->getWindowHeight());
	texts.emplace_back("Cancel", font, 0.33 * game_settings->getWindowWidth(), 0.9 * game_settings->getWindowHeight(), 0.08 * game_settings->getWindowHeight());
	texts.emplace_back("Create New World", font, 0.66 * game_settings->getWindowWidth(), 0.9 * game_settings->getWindowHeight(), 0.08 * game_settings->getWindowHeight());
	texts.emplace_back("World Name:", font, game_settings->getWindowWidth()/2, 0.15 * game_settings->getWindowHeight(), 0.08 * game_settings->getWindowHeight());
	texts.emplace_back("Seed:", font, game_settings->getWindowWidth() / 2, 0.4 * game_settings->getWindowHeight(), 0.08 * game_settings->getWindowHeight());

	for (int i = 2; i <= 3; i++)
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
				for (int i = 2; i <= 3; i++)
				{
					FloatRect textBounds = texts[i].getGlobalBounds();
					if (textBounds.contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
					{
						switch (i)
						{
						case 2:
						{

							return 2;
						}
						case 3:
						{
							game_settings->setWorld(texts[0].getString(), texts[1].getString());
							return 6;
						}
						default:
							break;
						}
					}
				}
				if (text_box1.getGlobalBounds().contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
				{
					wn= true;
					sn = false;
				}
				if (text_box2.getGlobalBounds().contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
				{
					sn = true;
					wn = false;
				}
			}
			else if (event.type == Event::TextEntered)
			{
				if (wn)
				{
					if (event.text.unicode == 8)
					{
						if (texts[0].getString().length() > 0)
						{
							texts[0].setString(texts[0].getString().substr(0, texts[0].getString().length() - 1));
						}
					}
					else if (event.text.unicode == 13)
					{
						wn = false;
					}
					else
					{
						if (texts[0].getString().length() < 28)
							texts[0].setString(texts[0].getString() + static_cast<char>(event.text.unicode));
					}
				}
				else if (sn)
				{
					if (event.text.unicode == 8)
					{
						if (texts[1].getString().length() > 0)
						{
							texts[1].setString(texts[1].getString().substr(0, texts[1].getString().length() - 1));
						}
					}
					else if (event.text.unicode == 13)
					{
						sn = false;
					}
					else
					{
						if (texts[1].getString().length() < 28)
							texts[1].setString(texts[1].getString() + static_cast<char>(event.text.unicode));
					}
				}
			}
		}

		for (int i = 2; i <= 3; i++)
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
		window.draw(text_box1);
		window.draw(text_box2);
		for (auto& text : texts)
		{
			window.draw(text);
		}
		window.display();
	}
}