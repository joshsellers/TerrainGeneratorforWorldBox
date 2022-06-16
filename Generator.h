#ifndef _GENERATOR_H
#define _GENERATOR_H

#include "PerlinNoise.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Generator {
public:
    Generator(const siv::PerlinNoise::seed_type seed);

    const sf::Image generate() const;

    void reseed(const siv::PerlinNoise::seed_type seed);
    const siv::PerlinNoise::seed_type getSeed();

    void setSize(int size);
    const int getSize();
private:
    siv::PerlinNoise::seed_type _seed;

    int _octaves = 4;
    int _size = 1000;
    double _sampleRate = 0.005;

    const sf::Image process(const std::vector<double>& data) const;
};

#endif

