#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(int seed) : seed(seed) {}

void WorldGenerator::generate(Chunk& ch)
{
    FastNoiseLite myNoise;
    myNoise.SetSeed(seed);
    
    // Tworzenie chunka
    for (int k = 0; k < chunkSizeY; ++k) {
        for (int j = ch.getChunkX() * chunkSizeX; j < chunkSizeX + (ch.getChunkX() * chunkSizeX); ++j) {
            // U¿yj generatora noise do uzyskania wartoœci dla danego punktu (x, y)
            float noiseValue = myNoise.GetNoise((float)j, (float)k);

            // Okreœlanie, czy punkt powinien byæ ziemi¹ czy powietrzem
            if (k < groundLevel + noiseValue * 10) {
                // Tworzenie bloku ziemi
                ch.setBlock(j, k, (short)1);
            }
            else {
                // Tworzenie bloku powietrza
                ch.setBlock(j, k, (short)0);
            }
        }
    }
}
