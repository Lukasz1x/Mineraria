#include "World.h"

World::World(string name, int seed, string seed_hash)
{
	cout<< "world: "<<name<<endl;
	cout << "seed: " << seed << endl;
	world_name = name;
	this->seed = seed;
	ifstream file("assets/blocks.txt");
	int id;
	string texture_png;
	while (file >> id)
	{
		file >> texture_png;
		textures.emplace_back(id, texture_png);
	}
	
	if (!std::filesystem::exists("saves/" + world_name))
	{
		std::filesystem::create_directory("saves/" + world_name);
		ofstream file("saves/" + world_name + "/world_info.txt", ios::out);
		file << seed_hash << endl;
		file.close();
		createNewWorld();
	}
	else
	{
		ifstream file("saves/" + world_name + "/world_info.txt");
		getline(file, seed_hash);
		file >> spawn_point.x >> spawn_point.y;
		file.close();
		load(0);
	}
}
	
void World::createNewWorld()
{
	unsigned int numThreads = std::thread::hardware_concurrency();
	numThreads = std::min(numThreads, static_cast<unsigned int>(chunks.size()));
	std::vector<std::thread> threads;
	for (int i = -10; i <= 10; i++)
	{
		chunks.emplace_back(i, seed);
	}
	for (size_t i = 0; i < chunks.size(); ++i)
	{
		// Utwórz w¹tek dla ka¿dego chunka
		auto generateThread = [this, i]() {
			this->generate(chunks[i]);
			};

		// Dodaj w¹tek do wektora
		threads.emplace_back(generateThread);

		// Jeœli osi¹gniêto maksymaln¹ liczbê w¹tków, poczekaj, a¿ jeden zakoñczy siê
		if (threads.size() >= numThreads)
		{
			for (auto& thread : threads)
			{
				thread.join();
			}
			threads.clear();
		}
	}

	// Poczekaj na pozosta³e w¹tki
	for (auto& thread : threads)
	{
		thread.join();
	}
	for (auto& chunk : chunks)
	{
		setTextures(chunk);
	}
	ofstream file("saves/" + world_name + "/world_info.txt", ios::app);
	for (auto& chunk : chunks)
	{
		if (chunk.getChunkX() == 0)
		{
			for(int i=319;i>0;i--)
				if (chunk.getBlockID(0, i) != 0)
				{
					spawn_point.y = i * 16;
				}
		}
	}
	spawn_point.x = 0;
	file << spawn_point.x << " " << spawn_point.y << endl;
	file.close();
}

void World::generate(Chunk& ch)
{
	cout << ch.getChunkX() << endl;
	generator.generate(ch);
	save(ch);
}

void World::setTextures(Chunk& ch)
{
	int chunk_x = ch.getChunkX();
	for (int y = 0; y < 320; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			if ((ch.getBlockID(x + chunk_x * 32, y) != 0))
			{
				for (auto& texture : textures)
				{
					if ((ch.getBlockID(x + chunk_x * 32, y) == texture.getID()))
					{
						ch.blocks[x][y].setTextture(texture.getTexture());
					}
				}
			}
		}
	}
}

void World::save(Chunk& ch)
{
	int chunk_x = ch.getChunkX();
    ofstream file("saves/"+world_name+"/"+to_string(ch.getChunkX())+".txt", ios::out);
	for (int y = 0; y < 320; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			file << ch.getBlockID(x + chunk_x * 32, y) << " ";
		}
		file << endl;
	}
	file.close();

}
void World::load(int chunk_x)
{
	for (int i = chunk_x - 10; i <= chunk_x + 10; i++)
	{
		bool found = 0;
		for (auto& chunk : chunks)
		{
			if (i == chunk.getChunkX())
			{
				found = true;
			}
		}
		if (!found)
		{
			chunks.emplace_back(i, seed);
			std::ifstream file("saves/" + world_name + "/" + to_string(i) + ".txt");

			// Sprawdzenie, czy plik istnieje
			if (file.is_open()) 
			{
				int chunk_x = chunks.back().getChunkX();
				int temp;
				for (int y = 0; y < 320; y++)
				{
					for (int x = 0; x < 32; x++)
					{
						file >> temp;
						chunks.back().setBlock(x + chunk_x * 32, y, temp);
					}
					
				}
			}
			else 
			{
				generate(chunks.back());
			}
			setTextures(chunks.back());
			file.close();
		}
		
	}
	
}

void World::unload(int chunk_x)
{
	for (auto it = chunks.begin(); it != chunks.end(); )
	{
		if ((it->getChunkX() > chunk_x + 20) || (it->getChunkX() < chunk_x - 20))
		{
			save(*it);
			it = chunks.erase(it);  // Usuñ obiekt i uzyskaj iterator do nastêpnego elementu
		}
		else
		{
			++it;  // PrzejdŸ do nastêpnego elementu
		}
	}
}

vector<Chunk>& World::getChunks()
{
	return chunks;
}


void convert(int& x, int& y, int &chunk_x)
{
	chunk_x = x / 512;
	if (x < 0)
	{
		chunk_x--;
		if (x%512==0)
		{
			chunk_x++;
			x = 0;
		}
	}
	while (x < 0)
	{
		x += (32 * 16);
	}
	while (x >= 512)
	{
		x -= (32 * 16);
	}
	if (y < 0)
	{
		y = 0; //bo nie wiadomo dlaczego myszka czasami ma ujemne kordy 
	}
	x /= 16;
	y /= 16;
}

short World::getBlockID(int x, int y)
{
	int chunk_x;
	convert(x, y, chunk_x);

	for (auto& chunk : chunks)
	{
		if (chunk.getChunkX() == chunk_x)
		{
			return chunk.getBlockID_PX(x, y);
		}
	}
}

void World::selectBlock(int x, int y)
{
	int chunk_x;
	convert(x, y, chunk_x);

	//cout << "world " << x << " " << y <<" "<<chunk_x<< endl;
	for (auto& chunk : chunks)
	{
		if (chunk.getChunkX() == chunk_x)
		{
			chunk.selectBlock(x, y);
		}
	}
}

void World::unselectBlock(int x, int y)
{
	int chunk_x;
	convert(x, y, chunk_x);
	for (auto& chunk : chunks)
	{
		if (chunk.getChunkX() == chunk_x)
		{
			chunk.unselectBlock(x, y);
		}
	}
}

void World::breakBlock(int x, int y)
{
	int chunk_x;
	convert(x, y, chunk_x);
	for (auto& chunk : chunks)
	{
		if (chunk.getChunkX() == chunk_x)
		{
			chunk.breakBlock(x, y);
		}
	}
}

Vector2f World::getSpawnPoint()
{
	return spawn_point;
}