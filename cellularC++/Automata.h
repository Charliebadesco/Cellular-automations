#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <ctime>
#include "Rule.h"


class Automata {
private:
    std::vector<std::vector<int>> grid;
    int width;
    int height;
    const Rule& rule;

public:
    Automata(int width, int height, const Rule& rule)
        : width(width), height(height), grid(height, std::vector<int>(width, 0)), rule(rule) {}

    void gridInitialisation(float livingDensity = 0.5f) {
        std::mt19937 gen(static_cast<unsigned>(time(0)));
        std::uniform_real_distribution<> distrib(0.0, 1.0);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                grid[y][x] = (distrib(gen) < livingDensity) ? 1 : 0;
            }
        }
    }

    int countNeighbors(int x, int y) const {
        int neighbors = 0;
        static const std::vector<std::pair<int, int>> directions = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, -1}, {-1, 1}
        };

        for (const auto& [dx, dy] : directions) {
            int nx = (x + dx + width) % width;
            int ny = (y + dy + height) % height;
            neighbors += grid[ny][nx];
        }

        return neighbors;
    }

    void update() {
        std::vector<std::vector<int>> newGrid = grid;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int neighbors = countNeighbors(x, y);
                newGrid[y][x] = rule.apply(grid[y][x], neighbors);
            }
        }

        grid = newGrid;
    }

    const std::vector<std::vector<int>>& getGrid() const {
        return grid;
    }
};

