#ifndef _UI_BUTTON_H
#define _UI_BUTTON_H

#include "UIElement.h"
#include "ButtonListener.h"

class UIButton : public UIElement {
public:
    UIButton(float x, float y, float width, float height,
        float scaleWidth, float scaleHeight, sf::String labelText, 
        sf::Font font, ButtonListener* listener, std::string code);

    void update();
    void draw(sf::RenderTexture& surface);

    void mouseButtonPressed(const int mx, const int my);
    void mouseButtonReleased(const int mx, const int my);
    void mouseMoved(const int mx, const int my);

private:
    bool _mouseDown = false;
    int _mx = 0, _my = 0;

    std::shared_ptr<sf::Texture> _hoverTexture =
        std::shared_ptr<sf::Texture>(new sf::Texture());
    std::shared_ptr<sf::Texture> _clickTexture =
        std::shared_ptr<sf::Texture>(new sf::Texture());

    ButtonListener* _listener = nullptr;
    std::string _buttonCode = "";
};

#endif

