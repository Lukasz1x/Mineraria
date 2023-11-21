#include "World.h"

World::World(string name, int seed)
{
	world_name = name;
	this->seed = seed;
	for (int i = -2; i <= -1; i++)
	{
		chunks.emplace_back(i);
	}
	WorldGenerator generator(seed);
	for (auto& chunk : chunks)
	{
		cout << chunk.getChunkX() << endl;
;		generator.generate(chunk);
		save(chunk);
	}
	
	
}

void World::save(Chunk& ch)
{
	if (!std::filesystem::exists("saves/" + world_name))
	{
		std::filesystem::create_directory("saves/" + world_name);
	}
    ofstream file("saves/"+world_name+"/"+to_string(ch.getChunkX())+".txt", ios::out);
	for (int y = 0; y < 320; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			file << ch.getBlockID(x, y) << " ";
		}
		file << endl;
	}
	file.close();

}
void World::load()
{

}
void World::unload()
{

}

vector<Chunk>& World::getChunks()
{
	return chunks;
}

