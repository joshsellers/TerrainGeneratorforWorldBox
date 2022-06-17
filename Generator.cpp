#include "Generator.h"
#include <iostream>

Generator::Generator(const siv::PerlinNoise::seed_type seed) {
    _seed = seed;
}

const sf::Image Generator::generate() {
    _isGenerating = true;

    std::vector<double> data(size*size);

    const siv::PerlinNoise perlin{ _seed };

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            double warpNoise = perlin.octave2D_01(
                warpSize*((double)x * sampleRate), 
                warpSize*((double)y * sampleRate), octaves
            );
            double noise = perlin.octave3D_01(
                (x) *sampleRate, (y) *sampleRate, 
                warpStrength * warpNoise, octaves
            );

            data[x + y * size] = noise;

            _progress = ((float)(x + y * size) / (float)(size * size));
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
    sf::Image image;
    image.create(size, size, sf::Color::Black);

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            sf::Uint32 val = 0xFF * data[x + y * size];
            sf::Uint32 color = val;
            color = ((color << 8) + val << 8) + val;
            image.setPixel(x, y, sf::Color((color << 8) + 0xFF));
        }
    }

    _isGenerating = false;
    return image;
}

void Generator::reseed(const siv::PerlinNoise::seed_type seed) {
    _seed = seed;
}

const siv::PerlinNoise::seed_type Generator::getSeed() {
    return _seed;
}

void Generator::setSize(int newSize) {
    size = newSize;
}

const int Generator::getSize() {
    return size;
}
