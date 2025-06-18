// AlertaAnim.cpp - Implementación de la animación de alerta
#include "AlertaAnim.hpp"
#include <iostream> // Para mensajes de error en consola

AlertaAnim::AlertaAnim() {
    bool cargada = textura.loadFromFile("assets/images/Alert_Ani_1.png");
    if (!cargada) {
        std::cerr << "[AlertaAnim] No se pudo cargar Alert_Ani_1.png\n";
        // Prueba con otra textura conocida
        cargada = textura.loadFromFile("assets/images/cake.png");
        if (cargada) {
            std::cerr << "[AlertaAnim] Se cargó cake.png como prueba.\n";
        } else {
            std::cerr << "[AlertaAnim] Tampoco se pudo cargar cake.png.\n";
        }
    }
    sprite.setTexture(textura);
    // Cambiar origen: centro de la imagen (como el personaje)
    sprite.setOrigin(textura.getSize().x/2.f, textura.getSize().y/2.f);
    visible = false;
    timer = 0.f;
    duracion = 1.0f; // Duración aumentada
    // Forzar color de fondo para detectar transparencia
    sprite.setColor(sf::Color(255, 255, 255, 255));
}

void AlertaAnim::activar(const sf::Vector2f& pos, float scale) {
    // Posicionar exactamente en el centro del personaje, pero 150 píxeles más arriba
    sprite.setPosition(pos.x, pos.y - 150.f * scale);
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
    if (visible) {
        window.draw(sprite);
    }
}

bool AlertaAnim::activa() const {
    return visible;
}

void AlertaAnim::forzarDesactivar() {
    visible = false;
    timer = 0.f;
}
