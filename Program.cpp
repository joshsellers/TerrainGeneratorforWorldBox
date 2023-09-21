#include "Program.h"

Program::Program(const int windowWidth, const int windowHeight) 
    : _generator(randomInt(10000, 99999)) {
    WINDOW_WIDTH = windowWidth;
    WINDOW_HEIGHT = windowHeight;

    _terrainTexture.create((int)_generator.size, (int)_generator.size);
    _terrainSprite.setTexture(_terrainTexture);

    float x = 1;
    float y = 10;
    int relativeX = (float) WINDOW_WIDTH * (x / 100);
    int relativeY = (float) WINDOW_HEIGHT * (y / 100);
    _terrainSprite.setPosition(relativeX, relativeY);

    float size = 43;
    float relativeSize = WINDOW_WIDTH * (size / 100);
    _terrainSprite.setScale(relativeSize / (int)_generator.size,
        relativeSize / (int)_generator.size);

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

    std::shared_ptr<UIButton> resetSeedButton = std::shared_ptr<UIButton>(
        new UIButton(58, 2, 15, 10, 10.5, 4.3, "New Seed", _font, this, "seed")
    );
    _uiElements.push_back(resetSeedButton);


    // TEXT FIELDS

    int xPos = 58;

    addTextField(xPos, 10, "seed: ", &_generator.seed);
    addTextField(xPos, 15, "size: ", &_generator.size);
    addTextField(xPos, 20, "octaves: ", &_generator.octaves);
    addTextField(xPos, 25, "sample rate: ", &_generator.sampleRate);
    addTextField(xPos, 30, "warp size: ", &_generator.warpSize);
    addTextField(xPos, 35, "warp strength: ", &_generator.warpStrength);

    addTextField(xPos, 45, "sea level: ", &_generator.seaLevel);
    addTextField(xPos, 50, "ocean mid: ", &_generator.oceanMidRange);
    addTextField(xPos, 55, "shallows: ", &_generator.oceanShallowRange);
    addTextField(xPos, 60, "sand: ", &_generator.sandRange);
    addTextField(xPos, 65, "dirt: ", &_generator.dirtHighRange);
    addTextField(xPos, 70, "mountains low: ", &_generator.mountainLowRange);
    addTextField(xPos, 75, "mountains high: ", &_generator.mountainMidRange);
    addTextField(xPos, 80, "snow caps: ", &_generator.mountainHighRange);

    addTextField(xPos + 27, 10, "edge strength: ", &_generator.waterEdgeStrength);
    addTextField(xPos + 27, 15, "biome edge mixing: ", &_generator.biomeEdgeMixing);
}

void Program::addTextField(int xPos, int yPos, std::string label, 
    double* valuePtr) {
    std::shared_ptr<UITextField> field = std::shared_ptr<UITextField>(
        new UITextField(
            xPos, yPos, 20, 10, 12, 4.3,
            std::to_string(*valuePtr), label, _font, valuePtr
        )
    );
    field->setEmptyValue(*valuePtr);
    _textFields.push_back(field);
    _uiElements.push_back(field);
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
        save();
    } else if (buttonCode == "seed") {
        srand(currentTimeMillis());
        int newSeed = randomInt(10000, 99999);

        _generator.seed = newSeed;
        _textFields[0].get()->setValue(newSeed);
        generate();
    }
}

void Program::generate() {
    float size = 43;
    float relativeSize = WINDOW_WIDTH * (size / 100);
    float scale = relativeSize / (int)_generator.size;
    _terrainSprite.setScale(scale, scale);

    _terrainTexture.create((int)_generator.size, (int)_generator.size);
    _terrainTexture.update(_generator.generate());
    _terrainSprite.setTexture(_terrainTexture);
    _terrainSprite.setTextureRect(
        sf::IntRect(0, 0, (int)_generator.size, (int)_generator.size)
    );
}

void Program::save() {
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

