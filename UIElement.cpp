#include "UIElement.h"

UIElement::UIElement(float x, float y, float width, float height,
    float scaleWidth, float scaleHeight, bool drawSprite, bool drawText, 
    sf::Font font) {
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _scaleWidth = scaleWidth;
    _scaleHeight = scaleHeight;
    _drawSprite = drawSprite;
    _drawText = drawText;

    _font = font;

    int relativeX = (float) WINDOW_WIDTH * (_x / 100);
    int relativeY = (float) WINDOW_HEIGHT * (_y / 100);
    _sprite.setPosition(relativeX, relativeY);

    float relativeWidth = WINDOW_WIDTH * (_scaleWidth / 100);
    float relativeHeight = WINDOW_HEIGHT * (_scaleHeight / 100);
    _sprite.setScale(relativeWidth / _width, relativeHeight / _height);
}

void UIElement::render(sf::RenderTexture& surface) {
    if (!_disableAutomaticTextAlignment) {
        _text.setPosition(
            _sprite.getPosition().x + _sprite.getGlobalBounds().width / 6,
            _sprite.getPosition().y + _sprite.getGlobalBounds().height / 6
        );
    }
    if (_drawSprite) surface.draw(_sprite);
    if (_drawText) surface.draw(_text);

    draw(surface);
}
