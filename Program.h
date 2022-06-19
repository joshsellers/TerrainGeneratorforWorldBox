#ifndef _PROGRAM_H
#define _PROGRAM_H

#include "Generator.h"
#include "UIButton.h"
#include "UITextField.h"
#include <iostream>
#include <regex>
#include <filesystem>
#include <sstream>

class Program : public ButtonListener {
public:
    Program(const int windowWidth, const int windowHeight);

    void update();
    void draw(sf::RenderTexture& surface);

    void keyPressed(const sf::Keyboard::Key& key);
    void keyReleased(const sf::Keyboard::Key& key);

    void mouseButtonPressed(const int mx, const int my);
    void mouseButtonReleased(const int mx, const int my);
    void mouseMoved(const int mx, const int my);

    void textEntered(sf::Uint32 character);

    void buttonPressed(std::string buttonCode);

    void uiSetup();

private:
    void generate();
    void save();

    void addTextField(int xPos, int yPos, std::string label, double* valuePtr);

    Generator _generator;

    sf::Texture _terrainTexture;
    sf::Sprite _terrainSprite;

    sf::RectangleShape _background;

    sf::RectangleShape _progBarBg;
    sf::RectangleShape _progBar;
    float _progBarMaxWidth = 0;

    std::vector<std::shared_ptr<UIElement>> _uiElements;
    std::vector<std::shared_ptr<UITextField>> _textFields;

    sf::Font _font;

    std::shared_ptr<UITextField> _seedField;
    std::shared_ptr<UITextField> _sizeField;
    std::shared_ptr<UITextField> _octavesField;
    std::shared_ptr<UITextField> _sampleRateField;
    std::shared_ptr<UITextField> _warpSizeField;
    std::shared_ptr<UITextField> _warpStrengthField;


    std::shared_ptr<UITextField> _seaLevelField;
    std::shared_ptr<UITextField> _oceanMidRangeField;
    std::shared_ptr<UITextField> _oceanShallowRangeField;
    std::shared_ptr<UITextField> _sandRangeField;
    std::shared_ptr<UITextField> _dirtHighRangeField;
    std::shared_ptr<UITextField> _mountainLowRangeField;
    std::shared_ptr<UITextField> _mountainMidRangeField;
    std::shared_ptr<UITextField> _mountainHighRangeField;
};

#endif

