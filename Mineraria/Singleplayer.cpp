#include "Singleplayer.h"

Singleplayer::Singleplayer(RenderWindow& window, GameSettings* game_settings) : window(window), game_settings(game_settings) {}

void Singleplayer::load()
{
	background_texture.loadFromFile("assets/background.png");
	background.setSize(Vector2f(game_settings->getWindowWidth(), game_settings->getWindowHeight()));
	background.setTexture(&background_texture);
	background.setPosition(0, 0);
	try {
		filesystem::directory_iterator it("saves");
		filesystem::directory_iterator end;

		while (it != end) {
			if (it->is_directory()) {
				std::string seed;
				std::ifstream file("saves/" + it->path().filename().string() + "/world_info.txt");

				if (file.is_open()) {
					getline(file, seed);
					file.close();
					worlds_data.emplace_back(it->path().filename().string(), seed);
				}
				else {
					std::cerr << "B³¹d otwarcia pliku dla œwiata " << it->path().filename().string() << std::endl;
				}
			}

			++it;
		}
	}
	catch (const std::exception& ex) {
		std::cerr << "B³¹d: " << ex.what() << std::endl;
		return;
	}

	for (auto& world : worlds_data)
	{
		cout << world.first << " " << world.second << endl;
		
	}
	x0 = 0.2 * game_settings->getWindowWidth();
	y0 = 0.25 * game_settings->getWindowHeight();
	for (int i = 0; i < worlds_data.size(); i++)
	{
		worlds.emplace_back();
		get<0>(worlds[i]).setSize(Vector2f(0.6 * game_settings->getWindowWidth(), 0.15 * game_settings->getWindowHeight()));
		get<0>(worlds[i]).setPosition(x0, y0 + i * 0.155 * game_settings->getWindowHeight());
		get<0>(worlds[i]).setFillColor(Color(255, 255, 255, 100));
		get<0>(worlds[i]).setOutlineColor(Color(0, 0, 0));
		get<0>(worlds[i]).setOutlineThickness(-0.01 * game_settings->getWindowHeight());
		get<1>(worlds[i]).setFont(font);
		get<1>(worlds[i]).setStyle(Text::Bold);
		get<1>(worlds[i]).setString(worlds_data[i].first);
		get<1>(worlds[i]).setCharacterSize(0.06 * game_settings->getWindowHeight());
		get<1>(worlds[i]).setFillColor(Color(0, 0, 0));
		get<1>(worlds[i]).setPosition(x0 + 0.02 * game_settings->getWindowWidth(), y0 + i * 0.155 * game_settings->getWindowHeight());
		get<2>(worlds[i]).setFont(font);
		get<2>(worlds[i]).setString(worlds_data[i].second);
		get<2>(worlds[i]).setCharacterSize(0.05 * game_settings->getWindowHeight());
		get<2>(worlds[i]).setFillColor(Color(0, 0, 0));
		get<2>(worlds[i]).setPosition(x0 + 0.02 * game_settings->getWindowWidth(), y0 + 0.065 * game_settings->getWindowHeight() + i * 0.155 * game_settings->getWindowHeight());
	}
}

int Singleplayer::run(std::string& world_name)
{
	load();
	vector<Writing>texts;
	font.loadFromFile("assets/fonts/andyb.ttf");
	texts.emplace_back("Select World", font, game_settings->getWindowWidth() / 2, 0.08 * game_settings->getWindowHeight(), 0.1 * game_settings->getWindowHeight());
	texts.emplace_back("Cancel", font, 0.33 * game_settings->getWindowWidth(), 0.9 * game_settings->getWindowHeight(), 0.08 * game_settings->getWindowHeight());
	texts.emplace_back("Create New World", font, 0.66 * game_settings->getWindowWidth(), 0.9 * game_settings->getWindowHeight(), 0.08 * game_settings->getWindowHeight());

	View main_view(FloatRect(0, 0, game_settings->getWindowWidth(), game_settings->getWindowHeight()));
	FloatRect box(0.2*game_settings->getWindowWidth(), 0.25*game_settings->getWindowHeight(), 0.6 * game_settings->getWindowWidth(), 0.5 * game_settings->getWindowHeight());
	View view(box);
	view.setViewport(sf::FloatRect(0.2f, 0.25, 0.6f, 0.5f));

	for (int i = 1; i < 3; i++)
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
							return 7;
						}
						default:
							break;
						}
					}
				}
				for (auto& world : worlds)
				{
					FloatRect worldBounds = get<0>(world).getGlobalBounds();
					if (worldBounds.contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
					{
						game_settings->setWorld(get<1>(world).getString(), get<2>(world).getString());
						return 6;
					}
				}	
			}
			else if (event.type == sf::Event::MouseWheelMoved)
			{
				if (box.contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
				{
					int move = 30*event.mouseWheel.delta;
					if (get<0>(worlds[0]).getPosition().y + move <= y0 && get<0>(worlds[worlds.size() - 1]).getPosition().y + move >= y0)
					{
						for (auto& world : worlds)
						{
							get<0>(world).move(0, move);
							get<1>(world).move(0, move);
							get<2>(world).move(0, move);
						}
					}
				}
			}
		}

		for (int i = 1; i < 3; i++)
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

		for (auto& world : worlds)
		{
			FloatRect worldBounds = get<0>(world).getGlobalBounds();
			if (box.contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
			{
				if (worldBounds.contains(static_cast<float>(Mouse::getPosition(window).x), static_cast<float>(Mouse::getPosition(window).y)))
				{
					get<0>(world).setOutlineColor(Color(155, 155, 100));
				}
				else
				{
					get<0>(world).setOutlineColor(Color(0, 0, 0));
				}
			}
			else
			{
				get<0>(world).setOutlineColor(Color(0, 0, 0));
			}
		}

		window.clear();
		window.setView(main_view);
		window.draw(background);
		for (auto& text : texts)
		{
			window.draw(text);
		}
		window.setView(view);
		for (auto& world : worlds)
		{
			window.draw(get<0>(world));
			window.draw(get<1>(world));
			window.draw(get<2>(world));
		}
		window.setView(main_view);
		window.display();
	}
}