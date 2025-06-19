#ifndef MUSIC_BUTTON_HPP
#define MUSIC_BUTTON_HPP

#include "Music.hpp"
#include <SFML/Graphics.hpp>

class MusicButton {
public:    MusicButton() {
        texture.loadFromFile("assets/images/speaker.png");
        // Reducir el tamaño del ícono a 1/4 del original
        sprite.setTexture(texture);
        sprite.setScale(0.04f, 0.04f); // Un poco más grande para la esquina superior izquierda
        // Posición en la esquina superior izquierda
        sprite.setPosition(0, 0); // Se ajusta dinámicamente
    }
    void draw(sf::RenderWindow& window) {
        // Posicionar en la esquina superior izquierda
        sf::Vector2u winSize = window.getSize();
        sf::FloatRect bounds = sprite.getGlobalBounds();
        float x = 20.f; // 20px del borde izquierdo
        float y = 20.f; // 20px del borde superior
        sprite.setPosition(x, y);
        window.draw(sprite);
        // Se quitó el contorno        // Se quitó el código del contorno
    }
    bool isClicked(const sf::Vector2i& mousePos) const {
        return sprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }
private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif // MUSIC_BUTTON_HPP
