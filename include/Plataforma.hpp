// Plataforma.hpp - Declaración de la clase Plataforma
#ifndef PLATAFORMA_HPP
#define PLATAFORMA_HPP
#include <SFML/Graphics.hpp>

class Plataforma {
public:
    Plataforma(const sf::Vector2f& pos, float scale = 1.0f);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
private:
    sf::Texture textura;
    sf::Sprite sprite;
};

#endif // PLATAFORMA_HPP
