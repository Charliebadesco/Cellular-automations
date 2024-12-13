#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Automata.h"
#include "Rule.h"
#include "ConwayRules.h"

int main() {
    int width = 100;
    int height = 80;
    float hexRadius = 10.f;
    float livingDensity = 0.2f;


    ConwayRules conwayRules;
    Automata Automata(width, height, conwayRules);

    sf::Music music;
    if (!music.openFromFile("Pufino.mp3")) {
        return EXIT_FAILURE; 
    }
    music.setLoop(true);
    music.play();

    //Automata.Automata(width, height, conwayRules);
    Automata.gridInitialisation(livingDensity);

    float windowWidth = width * hexRadius * 1.5f;
    float windowHeight = height * hexRadius * 1.732f; // Height multiplier for hexagon grid
    sf::RenderWindow window(sf::VideoMode(static_cast<int>(windowWidth), static_cast<int>(windowHeight)), 
                            "Hexagonal Cellular Automaton");

    sf::Clock clock;
    const int frameTimeMs = 100; 

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
                    sf::CircleShape hexagon(hexRadius, 6); 
                    float xOffset = (x + (y % 2) * 0.5f) * hexRadius * 1.5f;
                    float yOffset = y * hexRadius * 1.732f;
                    hexagon.setPosition(xOffset, yOffset);
                    hexagon.setFillColor(sf::Color::Green);
                    window.draw(hexagon);
                }
            }
        }

        window.display();
    }

    return 0;
}
