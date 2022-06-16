#ifndef _PROGRAM_H
#define _PROGRAM_H

#include "Generator.h"
#include "Util.h"
#include <iostream>

class Program {
public:
    Program(const int windowWidth, const int windowHeight);

    void update();
    void draw(sf::RenderTexture& surface);

    void keyPressed(const sf::Keyboard::Key& key);
    void keyReleased(const sf::Keyboard::Key& key);
private:
    int _windowWidth, _windowHeight;

    Generator _generator;

    sf::Texture _terrainTexture;
    sf::Sprite _terrainSprite;
};

#endif

