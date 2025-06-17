// AlertaAnim.cpp - Implementación de la animación de alerta
#include "AlertaAnim.hpp"
#include <iostream> // Para mensajes de error en consola

AlertaAnim::AlertaAnim() {
    if (!textura.loadFromFile("assets/images/Alert_Ani_1.png")) {
        std::cerr << "No se pudo cargar Alert_Ani_1.png\n";
    }
    sprite.setTexture(textura);
    sprite.setOrigin(textura.getSize().x/2.f, textura.getSize().y); // origen en la base
    visible = false;
    timer = 0.f;
    duracion = 1.0f; // Duración aumentada
}

void AlertaAnim::activar(const sf::Vector2f& pos, float scale) {
    // Posicionar justo sobre la cabeza del personaje
    sprite.setPosition(pos.x, pos.y - 60 * scale); // 60 px arriba del centro
    sprite.setScale(scale, scale);
    visible = true;
    timer = 0.f;
}

void AlertaAnim::update(float dt) {
    if (visible) {
        timer += dt;
        if (timer >= duracion) visible = false;
    }
}

void AlertaAnim::draw(sf::RenderWindow& window) {
    if (visible) window.draw(sprite);
}

bool AlertaAnim::activa() const {
    return visible;
}
