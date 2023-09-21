#include "Generator.h"
#include <iostream>
#include <algorithm>

Generator::Generator(const siv::PerlinNoise::seed_type seed) {
    this->seed = (double)seed;
}

const sf::Image Generator::generate() {
    _isGenerating = true;

    int intSize = (int)size;
    int intOctaves = (int)octaves;

    std::vector<double> data(intSize * intSize);

    const siv::PerlinNoise perlin{ (siv::PerlinNoise::seed_type)seed };

    std::vector<double> gradient(intSize * intSize);
    for (int y = 0; y < intSize; y++) {
        for (int x = 0; x < intSize; x++) {
            double midPoint = (double)intSize / 2;

            int xa = x;
            int ya = y;
            if (x > intSize / 2) {
                xa = intSize - x;
            }

            if (y > intSize / 2) {
                ya = intSize - y;
            }
            xa *= waterEdgeStrength;
            ya *= waterEdgeStrength;

            xa = std::min(midPoint, (double)xa);
            ya = std::min(midPoint, (double)ya);

            double gradientValue = 1.f - ((((double)xa / midPoint) * ((double)ya / midPoint)));
            gradient[x + y * intSize] = gradientValue;
        }
    }

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

            data[x + y * intSize] = noise - gradient[x + y * intSize];

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

            temperatureNoise += ((float)randomInt(-(int)biomeEdgeMixing, (int)biomeEdgeMixing)) / 100000.;
            precipitationNoise += ((float)randomInt(-(int)biomeEdgeMixing, (int)biomeEdgeMixing)) / 100000.;

            const float biomeSize = 0.00075;

            float tundraTemp = 0.460 + biomeSize;
            float tundraPrecLow = 0.340 - biomeSize;
            float tundraPrecHigh = 0.660 + biomeSize;

            float jungleTemp = 0.540 - biomeSize;
            float junglePrec = 0.460 + biomeSize;

            float savannaTemp = 0.540 - biomeSize;
            float savannaPrecLow = 0.315 - biomeSize;
            float savannaPrecHigh = 0.660 + biomeSize;

            bool tundra = temperatureNoise < tundraTemp && precipitationNoise >= tundraPrecLow && precipitationNoise < tundraPrecHigh;
            bool jungle = temperatureNoise > jungleTemp && precipitationNoise < junglePrec;
            bool savanna = temperatureNoise > savannaTemp && precipitationNoise >= savannaPrecLow && precipitationNoise < savannaPrecHigh;


            if (rgb == (sf::Uint32)TERRAIN_COLOR::DIRT_LOW || rgb == (sf::Uint32)TERRAIN_COLOR::DIRT_HIGH) {
                bool high = rgb == (sf::Uint32)TERRAIN_COLOR::DIRT_HIGH;

                if (tundra) {
                    rgb = high ? (sf::Uint32)TERRAIN_COLOR::SNOW_HIGH : (sf::Uint32)TERRAIN_COLOR::SNOW_LOW;
                } else if (jungle) {
                    rgb = high ? (sf::Uint32)TERRAIN_COLOR::JUNGLE_HIGH : (sf::Uint32)TERRAIN_COLOR::JUNGLE_LOW;
                } else if (savanna) {
                    rgb = high ? (sf::Uint32)TERRAIN_COLOR::SAVANNA_HIGH : (sf::Uint32)TERRAIN_COLOR::SAVANNA_LOW;
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