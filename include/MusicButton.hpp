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
    }
    bool isClicked(const sf::Vector2i& mousePos) const {
        return sprite.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }
private:
    sf::Texture texture;
    sf::Sprite sprite;
};
