#include "Generator.h"
#include <iostream>

Generator::Generator(const siv::PerlinNoise::seed_type seed) {
    this->seed = (double)seed;
}

const sf::Image Generator::generate() {
    _isGenerating = true;

    int intSize = (int)size;
    int intOctaves = (int)octaves;

    std::vector<double> data(intSize * intSize);

    const siv::PerlinNoise perlin{ (siv::PerlinNoise::seed_type)seed };

    for (int y = 0; y < intSize; y++) {
        for (int x = 0; x < intSize; x++) {
            double warpNoise = perlin.octave2D_01(
                warpSize*((double)x * sampleRate), 
                warpSize*((double)y * sampleRate), intOctaves
            );
            double noise = perlin.octave3D_01(
                (x) *sampleRate, (y) *sampleRate, 
                warpStrength * warpNoise, intOctaves
            );

            data[x + y * intSize] = noise;

            _progress = 
                ((float)(x + y * intSize) / (float)(intSize * intSize));
        }
    }

    return process(data, perlin);
}

float Generator::getProgress() const {
    return _progress;
}

bool Generator::isGenerating() const {
    return _isGenerating;
}

const sf::Image Generator::process(const std::vector<double>& data, const siv::PerlinNoise& perlin) {
    int intSize = (int)size;

    sf::Image image;
    image.create(intSize, intSize, sf::Color::Black);

    for (int y = 0; y < intSize; y++) {
        for (int x = 0; x < intSize; x++) {
            double val = data[x + y * intSize];

            sf::Uint32 rgb = 0x00;

            if (val >= seaLevel + mountainMidRange + mountainHighRange) {
                rgb = (sf::Uint32)TERRAIN_COLOR::MOUNTAIN_HIGH;
            } else if (val >= seaLevel + mountainLowRange + mountainMidRange) {
                rgb = (sf::Uint32)TERRAIN_COLOR::MOUNTAIN_MID;
            } else if (val >= seaLevel + dirtHighRange + mountainLowRange) {
                rgb = (sf::Uint32)TERRAIN_COLOR::MOUNTAIN_LOW;
            } else if (val >= seaLevel + sandRange + dirtHighRange) {
                rgb = (sf::Uint32)TERRAIN_COLOR::DIRT_HIGH;
            } else if (val >= seaLevel + sandRange) {
                rgb = (sf::Uint32)TERRAIN_COLOR::DIRT_LOW;
            } else if (val > seaLevel && val < seaLevel + sandRange) {
                rgb = (sf::Uint32)TERRAIN_COLOR::SAND;
            } else if (val > seaLevel - oceanShallowRange) {
                rgb = (sf::Uint32)TERRAIN_COLOR::WATER_SHALLOW;
            } else if (val > seaLevel - oceanMidRange) {
                rgb = (sf::Uint32)TERRAIN_COLOR::WATER_MID;
            } else if (val < seaLevel) {
                rgb = (sf::Uint32)TERRAIN_COLOR::WATER_DEEP;
            }
                    


            // biomes
            double xOffset = 20000.;
            double yOffset = 20000.;
            int biomeOctaves = 2;
            float biomeSampleRate = 0.001;
            double temperatureNoise = perlin.normalizedOctave3D_01((x + xOffset) * biomeSampleRate, (y + yOffset) * biomeSampleRate, 10, biomeOctaves);
            double precipitationNoise = perlin.normalizedOctave3D_01((x + xOffset) * biomeSampleRate, (y + yOffset) * biomeSampleRate, 40, biomeOctaves);

            float tundraTemp = 0.460 + 0.0075;
            float tundraPrecLow = 0.240 - 0.0075;
            float tundraPrecHigh = 0.660 + 0.0075;

            float jungleTemp = 0.540 - 0.0075;
            float junglePrec = 0.460 + 0.0075;

            float savannaTemp = 0.540 - 0.0075;
            float savannaPrecLow = 0.315 - 0.0075;
            float savannaPrecHigh = 0.660 + 0.0075;

            bool tundra = temperatureNoise < tundraTemp&& precipitationNoise >= tundraPrecLow && precipitationNoise < tundraPrecHigh;
            bool jungle = temperatureNoise > jungleTemp && precipitationNoise < junglePrec;
            bool savanna = temperatureNoise > savannaTemp && precipitationNoise >= savannaPrecLow && precipitationNoise < savannaPrecHigh;


            //std::cout << temperatureNoise << " " << precipitationNoise << std::endl;

            if (rgb == (sf::Uint32)TERRAIN_COLOR::DIRT_LOW || rgb == (sf::Uint32)TERRAIN_COLOR::DIRT_HIGH) {
                bool high = rgb == (sf::Uint32)TERRAIN_COLOR::DIRT_HIGH;

                if (tundra) {
                    rgb = high ? (sf::Uint32)TERRAIN_COLOR::SNOW_LOW : (sf::Uint32)TERRAIN_COLOR::SNOW_LOW;
                } else if (jungle) {
                    rgb = high ? (sf::Uint32)TERRAIN_COLOR::JUNGLE_HIGH : (sf::Uint32)TERRAIN_COLOR::JUNGLE_LOW;
                } else if (savanna) {
                    rgb = high ? (sf::Uint32)TERRAIN_COLOR::SAVANNA_HIGH : (sf::Uint32)TERRAIN_COLOR::SAVANNA_HIGH;
                } else {
                    rgb = high ? (sf::Uint32)TERRAIN_COLOR::GRASS_HIGH : (sf::Uint32)TERRAIN_COLOR::GRASS_LOW;
                }
            }


            image.setPixel(x, y, sf::Color((rgb << 8) + 0xFF));
        }
    }

    _isGenerating = false;
    return image;
}