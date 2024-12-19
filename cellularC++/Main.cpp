#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Automata.h"
#include "Rule.h"
#include "ConwayRules.h"
#include "MazeRules.h"
#include "HighLifeRules.h"
#include "ReplicatorRules.h"


int main() {
    int width = 300;
    int height = 200;
    float squareSize = 10.f; 
    float livingDensity = 0.2f;

    ConwayRules conwayRules;
    HighLifeRules highLifeRules;
    MazeRules mazeRules;
    ReplicatorRules replicatorRules;

    Automata Automata(width, height, mazeRules);

    sf::Music music;
    if (!music.openFromFile("Pufino.mp3")) {
        return EXIT_FAILURE; 
    }
    music.setLoop(true);
    music.play();

    Automata.gridInitialisation(livingDensity);

    float windowWidth = width * squareSize;
    float windowHeight = height * squareSize;
    sf::RenderWindow window(sf::VideoMode(static_cast<int>(windowWidth), static_cast<int>(windowHeight)), 
                            "Cellular Automaton");

    sf::Clock clock;
    const int frameTimeMs = 300; 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (clock.getElapsedTime().asMilliseconds() > frameTimeMs) {
            Automata.update();
            clock.restart();
        }

        window.clear();
        const auto& grid = Automata.getGrid();

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[y][x] == 1) {
                    sf::RectangleShape square(sf::Vector2f(squareSize, squareSize)); 
                    float xOffset = x * squareSize; 
                    float yOffset = y * squareSize; 
                    square.setPosition(xOffset, yOffset);
                    square.setFillColor(sf::Color::Green); 
                    window.draw(square); 
                }
            }
        }

        window.display();
    }

    return 0;
}
