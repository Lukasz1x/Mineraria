#include "WorldGenerator.h"

WorldGenerator::WorldGenerator() {}

void WorldGenerator::generate(Chunk& ch)
{
    FastNoiseLite myNoise;
    myNoise.SetSeed(ch.getSeed());

    const int maxIron = 15;
    const int maxCoal = 25;
    const int maxGold = 5;

    // Tworzenie chunka
    for (int k = 0; k < chunkSizeY; ++k)
    {
        for (int j = ch.getChunkX() * chunkSizeX; j < chunkSizeX + (ch.getChunkX() * chunkSizeX); ++j)
        {
            float noiseValue = myNoise.GetNoise((float)j, (float)k);

            // Okreœlanie, czy punkt powinien byæ kamieniem czy powietrzem
            if (k > groundLevel + noiseValue * 10) 
            {
                // Tworzenie bloku kamienia
                ch.setBlock(j, k, (short)1);

                // Generowanie ziemi 10 bloków od góry, a najwy¿szy blok to trawa
                if (k <= (groundLevel + noiseValue * 10 + 10)) 
                {

                    if (ch.getBlockID(j,k-1)==0) {
                        // Najwy¿szy blok to trawa
                        ch.setBlock(j, k, (short)2);
                    }
                    else {
                        // Pozosta³e bloki ziemi
                        ch.setBlock(j, k, (short)3);
                    }
                }
            

                // Generowanie surowców w kamieniu (deterministyczne)
                if (ch.getBlockID(j, k) == (short)1)
                {
                    unsigned int randValue = int(noiseValue * 1000);

                    // Ograniczenie iloœci surowców na chunk
                    int ironCount = 0;   // Iloœæ ¿elaza
                    int coalCount = 0;   // Iloœæ wêgla
                    int goldCount = 0;   // Iloœæ z³ota

                    // Przyk³adowe proporcje surowców: 20 ¿elaza, 30 wêgla, 10 z³ota

                    int resourceType = randValue % 23;

                    // 2% szans na generowanie surowców
                    if (resourceType == 0 && ironCount < maxIron)
                    {
                        // ¯elazo
                        ch.setBlock(j, k, (short)15);
                        ironCount++;
                    }
                    else if (resourceType == 1 && coalCount < maxCoal)
                    {
                        // Wêgiel
                        ch.setBlock(j, k, (short)16);
                        coalCount++;
                    }
                    else if (resourceType == 2 && goldCount < maxGold && k > 280)
                    {
                        // Z³oto
                        ch.setBlock(j, k, (short)14);
                        goldCount++;
                    }
                }
            }
            else
            {
                // Tworzenie bloku powietrza
                ch.setBlock(j, k, (short)0);
            }
            if (k == 319)
            {
                ch.setBlock(j, k, (short)7);
            }
        }
     }
}

