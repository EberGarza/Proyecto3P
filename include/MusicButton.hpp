#include "Music.hpp"
#include <SFML/Graphics.hpp>

class MusicButton {
public:
    MusicButton() {
        texture.loadFromFile("assets/images/speaker.png");
        sprite.setTexture(texture);
        sprite.setScale(0.08f, 0.08f); // Botón más pequeño
        // Centrar en la parte inferior central
        // La posición se ajustará en el draw usando el tamaño de la ventana
        sprite.setPosition(0, 0); // Se ajusta dinámicamente
    }
    void draw(sf::RenderWindow& window) {
        // Calcular posición centrada en la parte inferior
        sf::Vector2u winSize = window.getSize();
        sf::FloatRect bounds = sprite.getGlobalBounds();
        float x = (winSize.x - bounds.width) / 2.f;
        float y = winSize.y - bounds.height - 30.f; // 30px del borde inferior
        sprite.setPosition(x, y);
        window.draw(sprite);
        sf::RectangleShape outline(sf::Vector2f(bounds.width, bounds.height));
        outline.setPosition(x, y);
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
