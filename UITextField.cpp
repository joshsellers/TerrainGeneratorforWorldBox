#include "UITextField.h"

const sf::Uint32 TF_COLOR[] = { 0xC7, 0x77, 0x1A };
const sf::Uint32 TF_BORDER_COLOR[] = { 0xA3, 0x62, 0x15 };

UITextField::UITextField(float x, float y, float width, float height, 
    float scaleWidth, float scaleHeight,
    sf::String labelText, sf::String titleText, sf::Font font, 
    double* valuePtr) 
    : UIElement(
        x, y, width, height, scaleWidth, scaleHeight, true, true, font
    ) {

    _valuePtr = valuePtr;

    float fontSize = 1.5;
    int relativeFontSize = (float)WINDOW_WIDTH * (fontSize / 100);
    _text.setFont(_font);
    _text.setCharacterSize(relativeFontSize);
    _text.setFillColor(sf::Color::White);
    _text.setString(trimString(labelText));

    _title.setFont(_font);
    _title.setCharacterSize(relativeFontSize);
    _title.setFillColor(sf::Color::White);
    _title.setString(titleText);
    
    _userInput = trimString(labelText);

    int padding = 1;
    int w = (int)width;
    int h = (int)height;

    sf::Uint8* mainTexturePixels = new sf::Uint8[w * h * 4];
    for (int py = 0; py < h; py++) {
        for (int px = 0; px < w; px++) {
            mainTexturePixels[px * 4 + py * w * 4 + 0] = TF_COLOR[0];
            mainTexturePixels[px * 4 + py * w * 4 + 1] = TF_COLOR[1];
            mainTexturePixels[px * 4 + py * w * 4 + 2] = TF_COLOR[2];
            mainTexturePixels[px * 4 + py * w * 4 + 3] = 0xFF;
        }
    }

    _texture->create(width, height);
    _texture->update(mainTexturePixels);

    sf::Uint8* selectedPixels = new sf::Uint8[w * h * 4];
    for (int py = 0; py < h; py++) {
        for (int px = 0; px < w; px++) {
            if (px > padding / 2 && py > padding
                && px < w - padding && py < h - padding) {
                selectedPixels[px * 4 + py * w * 4 + 0] = TF_COLOR[0];
                selectedPixels[px * 4 + py * w * 4 + 1] = TF_COLOR[1];
                selectedPixels[px * 4 + py * w * 4 + 2] = TF_COLOR[2];
                selectedPixels[px * 4 + py * w * 4 + 3] = 0xFF;
            } else {
                selectedPixels[px * 4 + py * w * 4 + 0] = 
                    TF_BORDER_COLOR[0];
                selectedPixels[px * 4 + py * w * 4 + 1] = 
                    TF_BORDER_COLOR[1];
                selectedPixels[px * 4 + py * w * 4 + 2] = 
                    TF_BORDER_COLOR[2];
                selectedPixels[px * 4 + py * w * 4 + 3] = 0xFF;
            }
        }
    }

    _selectedTexture->create(width, height);
    _selectedTexture->update(selectedPixels);

    _sprite.setTexture(*_texture);

    delete[] mainTexturePixels;
    delete[] selectedPixels;

    _disableAutomaticTextAlignment = true;
}

void UITextField::update() {
    _text.setPosition(
        _sprite.getPosition().x,
        _sprite.getPosition().y + _sprite.getGlobalBounds().height / 6
    );

    _title.setPosition(
        _text.getPosition().x - _title.getGlobalBounds().width,
        _text.getPosition().y
    );
}

void UITextField::draw(sf::RenderTexture& surface) {
    surface.draw(_title);
}

void UITextField::textEntered(sf::Uint32 character) {
    if (character == '\b' && _userInput.getSize()) {
        _userInput.erase(_userInput.getSize() - 1, 1);
    } else if (character != '\b' && _userInput.getSize() < 13
        && character > 44 && character < 58) {
        _userInput += character;
    }
    _text.setString(_userInput);
}

void UITextField::mouseButtonPressed(const int mx, const int my) {
}

void UITextField::mouseButtonReleased(const int mx, const int my) {
    if (_sprite.getGlobalBounds().contains(mx, my)) {
        select();
    } else {
        deselect();
    }
}

void UITextField::mouseMoved(const int mx, const int my) {

}

void UITextField::select() {
    _selected = true;
    _sprite.setTexture(*_selectedTexture);
}

void UITextField::deselect() {
    _selected = false;
    _sprite.setTexture(*_texture);

    if (_userInput.getSize() == 0) {
        _userInput = trimString(std::to_string(_emptyValue));
        _text.setString(_userInput);
    } else {
        *_valuePtr = (double)getValue();
        _emptyValue = getValue();
    }
}

bool UITextField::isSelected() {
    return _selected;
}

void UITextField::setValue(float value) {
    _userInput = trimString(std::to_string(value));
    _text.setString(_userInput);
}

void UITextField::setEmptyValue(float value) {
    _emptyValue = value;
}

float UITextField::getValue() {
    return std::stof(_userInput.toAnsiString());
}

sf::FloatRect UITextField::getBounds() {
    return _sprite.getGlobalBounds();
}
