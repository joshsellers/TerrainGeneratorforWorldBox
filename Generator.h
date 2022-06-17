#ifndef _GENERATOR_H
#define _GENERATOR_H

#include "PerlinNoise.hpp"
#include "Util.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Generator {
public:
    Generator(const siv::PerlinNoise::seed_type seed);

    const sf::Image generate();

    void reseed(const siv::PerlinNoise::seed_type seed);
    const siv::PerlinNoise::seed_type getSeed();

    void setSize(int size);
    const int getSize();

    double warpSize = 4;
    double warpStrength = 0.8;

    int octaves = 4;
    int size = 1000;
    double sampleRate = 0.005;

    float getProgress() const;
    bool isGenerating() const;

private:
    siv::PerlinNoise::seed_type _seed;

    const sf::Image process(const std::vector<double>& data);

    float _progress = 0;
    bool _isGenerating = false;
};

#endif

