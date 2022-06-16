#include "Program.h"

Program::Program(const int windowWidth, const int windowHeight) 
    : _generator(randomInt(10000, 99999)) {
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;

    _terrainTexture.create(_generator.getSize(), _generator.getSize());
    _terrainSprite.setTexture(_terrainTexture);


    float x = 1;
    float y = 10;
    int relativeX = (float) _windowWidth * (x / 100);
    int relativeY = (float) _windowHeight * (y / 100);
    _terrainSprite.setPosition(relativeX, relativeY);

    float size = 43;
    float relativeSize = _windowWidth * (size / 100);
    _terrainSprite.setScale(relativeSize / _generator.getSize(), 
        relativeSize / _generator.getSize());
}

void Program::update() {
}

void Program::draw(sf::RenderTexture& surface) {
    surface.draw(_terrainSprite);
}

void Program::keyPressed(const sf::Keyboard::Key& key) {
}

void Program::keyReleased(const sf::Keyboard::Key& key) {
    if (key == sf::Keyboard::G) {
        _terrainTexture.update(_generator.generate());
    }
}
