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

    return process(data);
}

float Generator::getProgress() const {
    return _progress;
}

bool Generator::isGenerating() const {
    return _isGenerating;
}

const sf::Image Generator::process(const std::vector<double>& data) {
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
                    
            image.setPixel(x, y, sf::Color((rgb << 8) + 0xFF));
        }
    }

    _isGenerating = false;
    return image;
}