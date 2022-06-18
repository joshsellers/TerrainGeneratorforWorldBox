#include "Program.h"

Program::Program(const int windowWidth, const int windowHeight) 
    : _generator(randomInt(10000, 99999)) {
    WINDOW_WIDTH = windowWidth;
    WINDOW_HEIGHT = windowHeight;

    _terrainTexture.create(_generator.getSize(), _generator.getSize());
    _terrainSprite.setTexture(_terrainTexture);

    float x = 1;
    float y = 10;
    int relativeX = (float) WINDOW_WIDTH * (x / 100);
    int relativeY = (float) WINDOW_HEIGHT * (y / 100);
    _terrainSprite.setPosition(relativeX, relativeY);

    float size = 43;
    float relativeSize = WINDOW_WIDTH * (size / 100);
    _terrainSprite.setScale(relativeSize / _generator.getSize(), 
        relativeSize / _generator.getSize());

    int bgRelativeX = (float)WINDOW_WIDTH * ((x - 0.75) / 100);
    int bgRelativeY = (float)WINDOW_HEIGHT * ((y - 1.2) / 100);
    float bgRelativeSize = WINDOW_WIDTH * ((size + 1.5) / 100);
    _background = sf::RectangleShape(sf::Vector2f(
        bgRelativeSize,
        bgRelativeSize
    ));
    _background.setPosition(bgRelativeX, bgRelativeY);
    _background.setFillColor(sf::Color(30, 30, 30));


    // Progress bar

    float progBarX = 1.25;
    float progBarY = 93;
    float progBarWidth = 42.25;
    float progBarHeight = 1;

    int progBarBgRelX = (float)WINDOW_WIDTH * ((progBarX - 0.75) / 100);
    int progBarBgRelY = (float)WINDOW_HEIGHT * ((progBarY - 1.4) / 100);
    float progBarBgRelWidth = WINDOW_WIDTH * ((progBarWidth + 1.5) / 100);
    float progBarBgRelHeight = WINDOW_WIDTH * ((progBarHeight + 1.5) / 100);
    _progBarBg = sf::RectangleShape(sf::Vector2f(
        progBarBgRelWidth,
        progBarBgRelHeight
    ));
    _progBarBg.setPosition(progBarBgRelX, progBarBgRelY);
    _progBarBg.setFillColor(sf::Color(30, 30, 30));

    int progBarRelX = (float)WINDOW_WIDTH * ((progBarX) / 100);
    int progBarRelY = (float)WINDOW_HEIGHT * ((progBarY) / 100);
    float progBarRelWidth = WINDOW_WIDTH * ((progBarWidth) / 100);
    float progBarRelHeight = WINDOW_WIDTH * ((progBarHeight) / 100);
    _progBar = sf::RectangleShape(sf::Vector2f(
        progBarRelWidth,
        progBarRelHeight
    ));
    _progBar.setPosition(progBarRelX, progBarRelY);
    _progBar.setFillColor(sf::Color(200, 200, 220));
    _progBarMaxWidth = progBarRelWidth;

    //


    if (!_font.loadFromFile("font.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
    }

    uiSetup();
}

void Program::uiSetup() {
    // BUTTONS

    std::shared_ptr<UIButton> generateButton = std::shared_ptr<UIButton>(
        new UIButton(2, 2, 20, 10, 10, 4.3, "Generate", _font, this, "gen")
    );
    _uiElements.push_back(generateButton);

    std::shared_ptr<UIButton> saveButton = std::shared_ptr<UIButton>(
        new UIButton(15, 2, 8, 10, 5, 4.3, "Save", _font, this, "save")
        );
    _uiElements.push_back(saveButton);


    // TEXT FIELDS

    int xPos = 58;

    _seedField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 10, 20, 10, 12, 4.3,
            std::to_string(_generator.getSeed()), "seed: ", _font
        )
    );
    _seedField->setEmptyValue(_generator.getSeed());
    _textFields.push_back(_seedField);
    _uiElements.push_back(_seedField);

    _sizeField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 15, 20, 10, 12, 4.3,
            std::to_string(_generator.size), "size: ", _font
        )
        );
    _sizeField->setEmptyValue(_generator.size);
    _textFields.push_back(_sizeField);
    _uiElements.push_back(_sizeField);

    _octavesField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 20, 20, 10, 12, 4.3,
            std::to_string(_generator.octaves), "octaves: ", _font
        )
        );
    _octavesField->setEmptyValue(_generator.octaves);
    _textFields.push_back(_octavesField);
    _uiElements.push_back(_octavesField);

    _sampleRateField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 25, 20, 10, 12, 4.3,
            std::to_string(_generator.sampleRate), "sample rate: ", _font
        )
        );
    _sampleRateField->setEmptyValue(_generator.sampleRate);
    _textFields.push_back(_sampleRateField);
    _uiElements.push_back(_sampleRateField);

    _warpSizeField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 30, 20, 10, 12, 4.3,
            std::to_string(_generator.warpSize), "warp size: ", _font
        )
        );
    _warpSizeField->setEmptyValue(_generator.warpSize);
    _textFields.push_back(_warpSizeField);
    _uiElements.push_back(_warpSizeField);

    _warpStrengthField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 35, 20, 10, 12, 4.3,
            std::to_string(_generator.warpStrength), "warp strength: ", _font
        )
        );
    _warpStrengthField->setEmptyValue(_generator.warpStrength);
    _textFields.push_back(_warpStrengthField);
    _uiElements.push_back(_warpStrengthField);

    _seaLevelField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 45, 20, 10, 12, 4.3,
            std::to_string(_generator.seaLevel), "sea level: ", _font
        )
        );
    _seaLevelField->setEmptyValue(_generator.seaLevel);
    _textFields.push_back(_seaLevelField);
    _uiElements.push_back(_seaLevelField);

    _oceanMidRangeField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 50, 20, 10, 12, 4.3,
            std::to_string(_generator.oceanMidRange), "ocean mid: ", _font
        )
        );
    _oceanMidRangeField->setEmptyValue(_generator.oceanMidRange);
    _textFields.push_back(_oceanMidRangeField);
    _uiElements.push_back(_oceanMidRangeField);

    _oceanShallowRangeField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 55, 20, 10, 12, 4.3,
            std::to_string(_generator.oceanShallowRange), "shallows: ", _font
        )
        );
    _oceanShallowRangeField->setEmptyValue(_generator.oceanShallowRange);
    _textFields.push_back(_oceanShallowRangeField);
    _uiElements.push_back(_oceanShallowRangeField);

    _sandRangeField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 60, 20, 10, 12, 4.3,
            std::to_string(_generator.sandRange), "sand: ", _font
        )
        );
    _sandRangeField->setEmptyValue(_generator.sandRange);
    _textFields.push_back(_sandRangeField);
    _uiElements.push_back(_sandRangeField);

    _dirtHighRangeField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 65, 20, 10, 12, 4.3,
            std::to_string(_generator.dirtHighRange), "dirt: ", _font
        )
        );
    _dirtHighRangeField->setEmptyValue(_generator.dirtHighRange);
    _textFields.push_back(_dirtHighRangeField);
    _uiElements.push_back(_dirtHighRangeField);

    _mountainLowRangeField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 70, 20, 10, 12, 4.3,
            std::to_string(_generator.mountainLowRange), "mountain low: ", 
            _font
        )
        );
    _mountainLowRangeField->setEmptyValue(_generator.mountainLowRange);
    _textFields.push_back(_mountainLowRangeField);
    _uiElements.push_back(_mountainLowRangeField);

    _mountainMidRangeField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 75, 20, 10, 12, 4.3,
            std::to_string(_generator.mountainMidRange), "mountain high: ",
            _font
        )
        );
    _mountainMidRangeField->setEmptyValue(_generator.mountainMidRange);
    _textFields.push_back(_mountainMidRangeField);
    _uiElements.push_back(_mountainMidRangeField);

    _mountainHighRangeField = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, 80, 20, 10, 12, 4.3,
            std::to_string(_generator.mountainHighRange), "snow caps: ",
            _font
        )
        );
    _mountainHighRangeField->setEmptyValue(_generator.mountainHighRange);
    _textFields.push_back(_mountainHighRangeField);
    _uiElements.push_back(_mountainHighRangeField);
}

void Program::update() {
    for (auto& element : _uiElements) {
        element->update();
    }
}

void Program::draw(sf::RenderTexture& surface) {
    for (auto& element : _uiElements) {
        element->render(surface);
    }
  
    surface.draw(_background);
    
    if (_generator.isGenerating()) {
        _progBar.setSize(sf::Vector2f(
            _progBarMaxWidth * (_generator.getProgress()), _progBar.getSize().y)
        );

        surface.draw(_progBarBg);
        surface.draw(_progBar);
    } else {
        surface.draw(_terrainSprite);
    }
}

void Program::keyPressed(const sf::Keyboard::Key& key) {

}

void Program::keyReleased(const sf::Keyboard::Key& key) {

}

void Program::mouseButtonPressed(const int mx, const int my) {
    for (auto& element : _uiElements) {
        element->mouseButtonPressed(mx, my);
    }
}

void Program::mouseButtonReleased(const int mx, const int my) {
    for (auto& element : _uiElements) {
        element->mouseButtonReleased(mx, my);
    }
}

void Program::mouseMoved(const int mx, const int my) {
    for (auto& element : _uiElements) {
        element->mouseMoved(mx, my);
    }
}

void Program::textEntered(sf::Uint32 character) {
    for (auto& field : _textFields) {
        if (field->isSelected()) {
            field->textEntered(character);
        }
    }
}

void Program::buttonPressed(std::string buttonCode) {
    if (buttonCode == "gen") {
        generate();
    } else if (buttonCode == "save") {
        std::string pathStr = "";
        char* buf = nullptr;
        size_t sz = 0;
        if (_dupenv_s(&buf, &sz, "APPDATA") == 0 && buf != nullptr) {
            std::string temp(buf);
            pathStr = 
                std::regex_replace(
                    temp, std::regex("Roaming"), 
                    "LocalLow\\mkarpenko\\WorldBox\\saves"
                );
            free(buf);

            std::vector<std::string> folders;
            for (const auto& file 
                : std::filesystem::directory_iterator(pathStr)) {
                std::vector<std::string> seglist;
                std::stringstream pathStream(file.path().string());
                std::string segment = "";
                while (std::getline(pathStream, segment, '\\')) {
                    seglist.push_back(segment);
                }

                folders.push_back(seglist.at(seglist.size() - 1));
            }

            int highest = 0;
            for (std::string& folder : folders) {
                if (folder.find("save") != std::string::npos) {
                    std::string numStr = std::regex_replace(folder, std::regex("save"), "");
                    int num = std::stoi(numStr);
                    if (num > highest) highest = num;
                }
            }

            pathStr += "\\save" + std::to_string(highest + 1);

            try {
                if (!std::filesystem::create_directory(pathStr))
                    std::cerr << "Failed to create a directory\n"; \
            }
            catch (const std::exception& e) {
                std::cerr << e.what() << '\n';
            }

            if (_generator.generate().saveToFile(pathStr + "\\preview.png")) {
                std::cout << "Saved to " << pathStr << std::endl;
            } else {
                std::cout << "Failed to save" << std::endl;
            }

        } else {
            std::cout << "Path retrieval failed" << std::endl;
        }
    }
}

void Program::generate() {
    _generator.reseed(_seedField->getValue());
    _seedField->setEmptyValue(_generator.getSeed());

    _generator.size = _sizeField->getValue();
    _sizeField->setEmptyValue(_generator.size);

    _generator.octaves = _octavesField->getValue();
    _octavesField->setEmptyValue(_generator.octaves);

    _generator.sampleRate = _sampleRateField->getValue();
    _sampleRateField->setEmptyValue(_generator.sampleRate);

    _generator.warpSize = _warpSizeField->getValue();
    _warpSizeField->setEmptyValue(_generator.warpSize);

    _generator.warpStrength = _warpStrengthField->getValue();
    _warpStrengthField->setEmptyValue(_generator.warpStrength);

    _generator.seaLevel = _seaLevelField->getValue();
    _seaLevelField->setEmptyValue(_generator.seaLevel);

    _generator.oceanMidRange = _oceanMidRangeField->getValue();
    _oceanMidRangeField->setEmptyValue(_generator.oceanMidRange);

    _generator.oceanShallowRange = _oceanShallowRangeField->getValue();
    _oceanShallowRangeField->setEmptyValue(_generator.oceanShallowRange);

    _generator.sandRange = _sandRangeField->getValue();
    _sandRangeField->setEmptyValue(_generator.sandRange);

    _generator.dirtHighRange = _dirtHighRangeField->getValue();
    _dirtHighRangeField->setEmptyValue(_generator.dirtHighRange);

    _generator.mountainLowRange = _mountainLowRangeField->getValue();
    _mountainLowRangeField->setEmptyValue(_generator.mountainLowRange);

    _generator.mountainMidRange = _mountainMidRangeField->getValue();
    _mountainMidRangeField->setEmptyValue(_generator.mountainMidRange);

    _generator.mountainHighRange = _mountainHighRangeField->getValue();
    _mountainHighRangeField->setEmptyValue(_generator.mountainHighRange);


    float size = 43;
    float relativeSize = WINDOW_WIDTH * (size / 100);
    float scale = relativeSize / _generator.size;
    _terrainSprite.setScale(scale, scale);

    _terrainTexture.create(_generator.size, _generator.size);
    _terrainTexture.update(_generator.generate());
    _terrainSprite.setTexture(_terrainTexture);
    _terrainSprite.setTextureRect(
        sf::IntRect(0, 0, _generator.size, _generator.size)
    );
}

