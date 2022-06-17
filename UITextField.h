#ifndef _UI_TEXT_FIELD_H
#define _UI_TEXT_FIELD_H

#include "UIElement.h"
#include "Util.h"

class UITextField : public UIElement {
public:
    UITextField(float x, float y, float width, float height,
        float scaleWidth, float scaleHeight, 
        sf::String labelText, sf::String titleText, sf::Font font);

    void update();
    void draw(sf::RenderTexture& surface);

    void textEntered(sf::Uint32 character);
    void mouseButtonPressed(const int mx, const int my);
    void mouseButtonReleased(const int mx, const int my);
    void mouseMoved(const int mx, const int my);

    void select();
    void deselect();
    bool isSelected();

    void setValue(float value);
    void setEmptyValue(float value);
    float getValue();

    sf::FloatRect getBounds();
private:
    sf::Text _title;

    sf::String _userInput;

    bool _selected = false;

    std::shared_ptr<sf::Texture> _selectedTexture =
        std::shared_ptr<sf::Texture>(new sf::Texture());

    float _emptyValue = 0;
};

#endif

