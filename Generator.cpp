#include "Generator.h"

Generator::Generator(const siv::PerlinNoise::seed_type seed) {
    _seed = seed;
}

const sf::Image Generator::generate() const {
    std::vector<double> data(_size*_size);

    const siv::PerlinNoise perlin{ _seed };

    double warpSize = 4;
    double warpStrength = 0.8;

    for (int y = 0; y < _size; y++) {
        for (int x = 0; x < _size; x++) {
            double warpNoise = perlin.octave2D_01(
                warpSize*((double)x * _sampleRate), 
                warpSize*((double)y * _sampleRate), _octaves
            );
            double noise = perlin.octave3D_01(
                (x) *_sampleRate, (y) *_sampleRate, 
                warpStrength * warpNoise, _octaves
            );

            data[x + y * _size] = noise;
        }
    }

    return process(data);
}

const sf::Image Generator::process(const std::vector<double>& data) const {
    sf::Image image;
    image.create(_size, _size, sf::Color::Black);

    for (int y = 0; y < _size; y++) {
        for (int x = 0; x < _size; x++) {
            sf::Uint32 val = 0xFF * data[x + y * _size];
            sf::Uint32 color = val;
            color = ((color << 8) + val << 8) + val;
            image.setPixel(x, y, sf::Color((color << 8) + 0xFF));
        }
    }

    return image;
}

void Generator::reseed(const siv::PerlinNoise::seed_type seed) {
    _seed = seed;
}

const siv::PerlinNoise::seed_type Generator::getSeed() {
    return _seed;
}

void Generator::setSize(int size) {
    _size = size;
}

const int Generator::getSize() {
    return _size;
}
