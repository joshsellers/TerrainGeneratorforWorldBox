#ifndef _UI_ELEMENT_H
#define _UI_ELEMENT_H

#include <memory>
#include "Globals.h"
#include <SFML/Graphics.hpp>

class UIElement {
public:
    UIElement(float x, float y, float width, float height,
        float scaleWidth, float scaleHeight, bool drawSprite, bool drawText, 
        sf::Font font);

    virtual void update() = 0;
    virtual void draw(sf::RenderTexture& surface) = 0;
    void render(sf::RenderTexture& surface);

    virtual void mouseButtonPressed(const int mx, const int my) = 0;
    virtual void mouseButtonReleased(const int mx, const int my) = 0;
    virtual void mouseMoved(const int mx, const int my) = 0;
    
protected:
    float _x, _y;
    float _width, _height;
    float _scaleWidth, _scaleHeight;

    std::shared_ptr<sf::Texture> _texture = 
        std::shared_ptr<sf::Texture>(new sf::Texture());
    sf::Sprite _sprite;

    sf::Text _text;
    sf::Font _font;

    bool _disableAutomaticTextAlignment = false;

private:
    bool _drawSprite = true;
    bool _drawText = true;
};

#endif

