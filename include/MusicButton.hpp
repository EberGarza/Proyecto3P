#ifndef MUSIC_BUTTON_HPP
#define MUSIC_BUTTON_HPP

#include "Music.hpp"
#include <SFML/Graphics.hpp>

class MusicButton {
public:
    MusicButton() {
        texture.loadFromFile("assets/images/speaker.png");
        // Reducir el tamaño del ícono a 1/4 del original
        sprite.setTexture(texture);
        sprite.setScale(0.02f, 0.02f); // Mucho más pequeño
        // Centrar en la parte inferior central
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
        // Hacer el contorno rojo apenas más grande que el ícono
        float outlineW = bounds.width + 4.f;
        float outlineH = bounds.height + 4.f;
        float outlineX = x - 2.f;
        float outlineY = y - 2.f;
        sf::RectangleShape outline(sf::Vector2f(outlineW, outlineH));
        outline.setPosition(outlineX, outlineY);
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

#endif // MUSIC_BUTTON_HPP
