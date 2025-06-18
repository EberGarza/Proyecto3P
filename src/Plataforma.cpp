// Plataforma.cpp - Implementación de la clase Plataforma
#include "Plataforma.hpp"
#include <iostream>

Plataforma::Plataforma(const sf::Vector2f& pos, float scale) {
    if (!textura.loadFromFile("assets/images/Platform.png")) {
        std::cerr << "No se pudo cargar Platform.png\n";
    }
    sprite.setTexture(textura);
    sprite.setOrigin(textura.getSize().x/2.f, textura.getSize().y/2.f);
    sprite.setScale(scale, scale);
    sprite.setPosition(pos);
}

void Plataforma::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Plataforma::getBounds() const {
    return sprite.getGlobalBounds();
}
