#include "Music.hpp"
#include <SFML/Graphics.hpp>

class MusicButton {
public:
    MusicButton() {
        texture.loadFromFile("assets/images/speaker.png");
        sprite.setTexture(texture);
        sprite.setScale(0.08f, 0.08f); // Botón más pequeño
        sprite.setPosition(40, 40); // Esquina superior izquierda
    }
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
        // Dibuja un contorno rojo alrededor del botón
        sf::FloatRect bounds = sprite.getGlobalBounds();
        sf::RectangleShape outline(sf::Vector2f(bounds.width, bounds.height));
        outline.setPosition(bounds.left, bounds.top);
        outline.setFillColor(sf::Color::Transparent);
        outline.setOutlineColor(sf::Color::Red);
        outline.setOutlineThickness(2.f);
        window.draw(outline);
    }
    bool isClicked(const sf::Vector2i& mousePos) const {
        return sprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }
private:
    sf::Texture texture;
    sf::Sprite sprite;
};
