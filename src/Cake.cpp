// Cake.cpp - Implementación de la clase Cake
#include "Cake.hpp"
#include <vector>
#include <string>

Cake::Cake(const sf::Vector2f& pos) : position(pos) {
    // Cargar todos los frames de animación
    std::vector<std::string> nombres = {
        "assets/images/cake.png",           // 0: normal
        "assets/images/Cake_Anim_1.png",    // 1
        "assets/images/Cake_Anim_2.png",    // 2
        "assets/images/Cake_Anim_3.png",    // 3
        "assets/images/Cake_Re_Anim_2.png", // 4
        "assets/images/Cake_Re_Anim_1.png"  // 5
    };
    animFrames.resize(nombres.size());
    for (size_t i = 0; i < nombres.size(); ++i) {
        animFrames[i].loadFromFile(nombres[i]);
    }
    animFrame = 0;
    sprite.setTexture(animFrames[0]);
    // Escalado responsivo: el dulce debe ocupar ~4% del alto de la ventana (más pequeño)
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    float targetHeight = vm.height * 0.04f;
    float scale = targetHeight / animFrames[0].getSize().y;
    sprite.setScale(scale, scale);
    sprite.setOrigin(animFrames[0].getSize().x/2.f, animFrames[0].getSize().y/2.f);
    sprite.setPosition(position);
    animTimer = 0.f;
    animElapsed = 0.f;
    animando = false;
}

void Cake::iniciarAnimacion() {
    animando = true;
    animFrame = 1; // Comienza con el primer frame de brillo
    animTimer = 0.f;
}

void Cake::update(float dt) {
    animElapsed += dt;
    if (!animando && animElapsed >= animInterval) {
        iniciarAnimacion();
        animElapsed = 0.f;
    }
    if (animando) {
        animTimer += dt;
        if (animTimer >= animSpeed) {
            animTimer = 0.f;
            // Secuencia: 1,2,3,4,5,0
            static const int secuencia[] = {1,2,3,4,5,0};
            int idx = -1;
            for (int i = 0; i < 6; ++i) if (animFrame == secuencia[i]) idx = i;
            if (idx != -1 && idx < 5) {
                animFrame = secuencia[idx+1];
                sprite.setTexture(animFrames[animFrame]);
            } else {
                animando = false;
                animFrame = 0;
                sprite.setTexture(animFrames[0]);
            }
        }
    }
}

void Cake::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Cake::getPosition() const {
    return position;
}

void Cake::setPosition(const sf::Vector2f& pos) {
    position = pos;
    sprite.setPosition(position);
}

float Cake::getRadius() const {
    return radius * sprite.getScale().y;
}
