// Rope.hpp - Declaración de la clase Rope (cuerda)
#ifndef ROPE_HPP
#define ROPE_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class Rope {
public:
    Rope(const sf::Vector2f& start, const sf::Vector2f& end, int segments = 20);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void setFixedStart(bool fixed); // Fijar el extremo inicial
    void setFixedEnd(bool fixed);   // Fijar el extremo final
    std::vector<sf::Vector2f>& getPoints();
private:
    std::vector<sf::Vector2f> points;         // Posición actual de cada nodo
    std::vector<sf::Vector2f> prevPoints;     // Posición previa (para Verlet)
    std::vector<sf::CircleShape> nodes;       // Visualización
    sf::Color color;
    int numSegments;
    bool fixedStart = true;
    bool fixedEnd = false;
    sf::Vector2f gravity = sf::Vector2f(0.f, 600.f); // px/s^2
    int constraintIterations = 15;
    // Asset gráfico para la cuerda
    sf::Texture ropeTexture;
    sf::Sprite ropeSprite;
};

#endif // ROPE_HPP
