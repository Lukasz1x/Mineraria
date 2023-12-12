#include "Game.h"

Game::Game(RenderWindow& window, GameSettings& game_settings) : window(window), game_settings(game_settings) {}

void Game::load()
{
	background_texture.loadFromFile("assets/background_sky.png");
	background.setSize(Vector2f(800, 480));
	background.setTexture(&background_texture);
	background.setOrigin(400, 240);
	background.setScale(5, 5);
}

void Game::load_unload(World& world)
{
	chrono::milliseconds interval(100);
	auto startTime = std::chrono::steady_clock::now();
	while(window.isOpen())
	{ 
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
		if (elapsedTime >= interval)
		{	
			View current_view = window.getView();
			int x = current_view.getCenter().x / 512;
			world.load(x);
			world.unload(x);
			cout << "Load" << endl;
			startTime = std::chrono::steady_clock::now();
		}

	}
}

void check_colisions(World& world, int& top, int& down, int& left, int& right, FloatRect position)
{
	top = (int)((position.top - 50) / 16) * 16;
	left = (int)((position.left - 50) / 16) * 16;
	right = (int)((position.left + position.width + 50) / 16) * 16;
	down = (int)((position.top + position.height + 50) / 16) * 16;
	int loop1 = right;
	int loop2 = down;
	for (int x = left; x <= loop1; x += 16)
	{
		for (int y = top; y <= loop2; y += 16)
		{
			//cout << "Kolizje petla " << x << " " << y << endl;
			if (world.getBlockID(x, y) != 0)
			{
				FloatRect d(position.left, position.top - 32, position.width, position.height + 64);
				if (d.intersects(FloatRect(x, y, 16, 16)) &&  (y >=  position.top+position.height))
				{
					if (y < down)
					{
						
						down = y;
					}
				}
				if (d.intersects(FloatRect(x, y, 16, 16)) && (y <= position.top))
				{
					if (y > top)
					{

						top = y;
					}
				}
				FloatRect l(position.left - 32, position.top, position.width + 64, position.height);
				if (l.intersects(FloatRect(x, y, 16, 16)) && (x >= position.left + position.width))
				{
					if (x < right)
					{

						right = x;
					}
				}
				if (l.intersects(FloatRect(x, y, 16, 16)) && (x <= position.left))
				{
					if (x > left)
					{

						left = x;
					}
				}
			}
		}
	}
	left += 16;
	top += 16;
}

void Game::update(World& world)
{
	chrono::milliseconds interval(25);
	auto startTime = std::chrono::steady_clock::now();
	int top, down, left, right;
	while (window.isOpen())
	{
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
		//check_colisions(world, top, down, left, right, player.getHitBox());
		if (elapsedTime >= interval)
		{
			player.applyGravity();
			check_colisions(world, top, down, left, right, player.getHitBox());
			player.updatePosition(top, down, left, right);
			startTime = std::chrono::steady_clock::now();
		}
	}
}

void Game::cursor(World& world)
{
	Vector2i selected = Vector2i(0, 0);
	while (window.isOpen())
	{
		Vector2i mouse = Mouse::getPosition(window);
		Vector2f worldMouse = window.mapPixelToCoords(mouse);
		int left = ((int)((worldMouse.x - 18) / 16)) * 16;
		int top = ((int)((worldMouse.y - 18) / 16)) * 16;
		//cout << "myszka " << mouse.x << " " << mouse.y << endl;
		//cout << "Myszka world "<<worldMouse.x << " " << worldMouse.y << endl;
		//cout <<"rogi "<< left << " " << top << endl;
		for (int x = left; x <= left + 40; x += 16)
		{
			for (int y = top; y <= top + 40; y += 16)
			{			
				FloatRect block(x, y, 16, 16);
				if (block.contains(worldMouse))
				{
					cout <<"petla "<< x << " " << y << endl;
					world.selectBlock(x, y);
					if (selected!=Vector2i(x,y))
					{
						world.unselectBlock(selected.x, selected.y);
						
						selected = Vector2i(x, y);
					}
				}
			}
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			world.breakBlock(selected.x, selected.y);
		}
	}
}

int Game::run()
{
	View main_view(FloatRect(0, 0, game_settings.getWindowWidth()/2, game_settings.getWindowHeight()/2));
	load();
	window.setView(main_view);
	World world("New World", 123);
	//thread t(&Game::load_unload, this, ref(world));
	//t.detach();
	thread update_thread(&Game::update, this, ref(world));
	update_thread.detach();
	thread cursor_thread(&Game::cursor, this, ref(world));
	cursor_thread.detach();
	

	while (window.isOpen())
	{

		if (Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			player.setVelocity(Vector2f(0, -100));
			}
		if (Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.setVelocity(Vector2f(80, player.getVelocity().y));
			}
		else if (Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player.setVelocity(Vector2f(-80, player.getVelocity().y));

		}
		else
		{
			player.setVelocity(Vector2f(0, player.getVelocity().y));
		}
		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed)
				window.close();
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Subtract))
			{
				if (zoom > 1)
				{
					main_view.zoom(2.0f);
					zoom--;
				}		
			}
			else if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Add))
			{
				if (zoom < 5)
				{
					main_view.zoom(0.5f);
					zoom++;
				}
			}
			
		}
		main_view.setCenter(player.getCenter());
		window.setView(main_view);
		FloatRect view;
		view = FloatRect(main_view.getCenter().x - main_view.getSize().x / 2 - 20, main_view.getCenter().y - main_view.getSize().y / 2 - 20, main_view.getSize().x + 40, main_view.getSize().y + 40);
		//cout << view.left << " " << view.top << " " << view.width << " " << view.height << " " << current_view.getCenter().x << " " << current_view.getCenter().y << endl;
		background.setPosition(main_view.getCenter().x, main_view.getCenter().y);
		int x = main_view.getCenter().x / 512;
		world.load(x);
		world.unload(x);
		window.clear();
		window.draw(background);
		for (auto& chunk : world.getChunks())
		{
			//cout << chunk.blocks[0][0].block.getPosition().x << endl;
			if (((chunk.getChunkX() * 32 * 16) >= view.left - 512 - 20) && ((chunk.getChunkX() * 32 * 16) <= view.left + main_view.getSize().y + 512 + 64))
			{
				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 320; j++)
					{
						if (view.contains(Vector2f((chunk.getChunkX() * 32 + i) * 16, 16 * j)))
						{
							//cout << i << " " << j << endl;
							window.draw(chunk.block(i, j));
						}
					}
				}
			}
		}
		window.draw(player);
		window.display();



	}
	return 1;
}