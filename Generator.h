#ifndef _GENERATOR_H
#define _GENERATOR_H

#include "PerlinNoise.hpp"
#include "Util.h"
#include <vector>
#include <SFML/Graphics.hpp>

enum class TERRAIN_COLOR : sf::Uint32 {
    WATER_DEEP      = 0x3370cc,
    WATER_MID       = 0x4084e2,
    WATER_SHALLOW   = 0x55aef0,

    SAND            = 0xf7e898,
    DIRT_LOW        = 0xd58e12,
    DIRT_HIGH       = 0xb66f3a,

    MOUNTAIN_LOW    = 0x5b5e5c,
    MOUNTAIN_MID    = 0x414545,
    MOUNTAIN_HIGH   = 0xe2edec
};

class Generator {
public:
    Generator(const siv::PerlinNoise::seed_type seed);

    const sf::Image generate();

    double warpSize = 4;
    double warpStrength = 0.8;

    double seed; // cast to siv::PerlinNoise::seed_type

    double octaves = 4; // cast to int 
    double size = 1500; // cast to int
    double sampleRate = 0.005;

    double seaLevel = 0.5;

    double oceanMidRange = 0.045;
    double oceanShallowRange = 0.01;
    double sandRange = 0.02;
    double dirtHighRange = 0.05;
    double mountainLowRange = 0.1;
    double mountainMidRange = 0.1;
    double mountainHighRange = 0.2;

    float getProgress() const;
    bool isGenerating() const;

private:
    const sf::Image process(const std::vector<double>& data);

    float _progress = 0;
    bool _isGenerating = false;
};

#endif

