#include <string>
#include "Program.h"


int main() {
    std::string VERSION = "0.1";
    int WIDTH = sf::VideoMode::getDesktopMode().width / 1.5;
    int HEIGHT = sf::VideoMode::getDesktopMode().height / 1.5;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), 
        "Terrain Generator for World Box (v. " + VERSION + ")");
    window.setFramerateLimit(60);

    srand(currentTimeMillis());
    Program program(WIDTH, HEIGHT);

    sf::Event event;

    sf::RenderTexture mainSurface;
    mainSurface.create(WIDTH, HEIGHT);
    const sf::Texture& mainSurfaceTexture = mainSurface.getTexture();

    sf::Sprite mainSurfaceSprite;
    mainSurfaceSprite.setTexture(mainSurfaceTexture);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    program.keyPressed(event.key.code);
                    break;
                case sf::Event::KeyReleased:
                    program.keyReleased(event.key.code);
                    break;
            }
        }

        program.update();

        mainSurface.clear(sf::Color(45, 45, 48, 255));
        program.draw(mainSurface);
        mainSurface.display();

        window.clear();
        window.draw(mainSurfaceSprite);
        window.display();
    }
}