#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

class AutomateCellulaire {
private:
    std::vector<std::vector<int>> grille;
    int largeur;
    int hauteur;

public:
    AutomateCellulaire(int largeur, int hauteur)
        : largeur(largeur), hauteur(hauteur), grille(hauteur, std::vector<int>(largeur, 0)) {}

    void initialiserAleatoirement() {
        srand(static_cast<unsigned>(time(0)));
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                grille[y][x] = rand() % 2;
            }
        }
    }

    int compterVoisins(int x, int y) const {
        int voisins = 0;
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0) continue;
                int nx = (x + dx + largeur) % largeur;
                int ny = (y + dy + hauteur) % hauteur;
                voisins += grille[ny][nx];
            }
        }
        return voisins;
    }

    void mettreAJour() {
        std::vector<std::vector<int>> nouvelleGrille = grille;
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                int voisins = compterVoisins(x, y);
                if (grille[y][x] == 1) {
                    nouvelleGrille[y][x] = (voisins == 2 || voisins == 3) ? 1 : 0;
                } else {
                    nouvelleGrille[y][x] = (voisins == 3) ? 1 : 0;
                }
            }
        }
        grille = nouvelleGrille;
    }

    const std::vector<std::vector<int>>& getGrille() const {
        return grille;
    }
};

int main() {
    int largeur = 40;
    int hauteur = 30;
    int tailleCellule = 20;

    AutomateCellulaire automate(largeur, hauteur);
    automate.initialiserAleatoirement();

    sf::RenderWindow window(sf::VideoMode(largeur * tailleCellule, hauteur * tailleCellule), "Automate Cellulaire");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Mettre à jour l'automate
        automate.mettreAJour();

        // Dessiner la grille
        window.clear();
        const auto& grille = automate.getGrille();
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                sf::RectangleShape cellule(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));
                cellule.setPosition(x * tailleCellule, y * tailleCellule);
                cellule.setFillColor(grille[y][x] ? sf::Color::Green : sf::Color::Black);
                window.draw(cellule);
            }
        }
        window.display();

        // Attendre un peu avant la prochaine génération
        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}
