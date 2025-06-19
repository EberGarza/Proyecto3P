#include "Estrella.hpp"
#include <iostream>
#include <cmath> // Para usar sin()

Estrella::Estrella() :
    frameActual(0),
    tiempoAcumulado(0.0f),
    duracionFrame(0.15f),
    recogida(false),
    animacionFinalizada(false),
    tiempoEfecto(0.0f)
{
    // Primero redimensionar el vector antes de acceder a sus elementos
    texturas.resize(1); // Solo necesitamos un frame para la apariencia inicial
    
    // Luego cargar la textura
    if (!texturas[0].loadFromFile("assets/images/Star_Succesion_0.png")) {
        std::cerr << "Error al cargar la textura de la estrella: Star_Succesion_0.png" << std::endl;
    } else {
        // Solo configurar el sprite si la textura se cargó correctamente
        sprite.setTexture(texturas[0]);
        
        // Centrar origen en el centro de la textura
        sf::Vector2u texSize = texturas[0].getSize();
        sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
    }
}

Estrella::~Estrella() {
    // No es necesario liberar recursos de SFML
}

void Estrella::inicializar(float x, float y, float escala) {
    sprite.setPosition(x, y);
    sprite.setScale(escala, escala);
    frameActual = 0;
    tiempoAcumulado = 0.0f;
    tiempoEfecto = 0.0f;
    recogida = false;
    animacionFinalizada = false;
    sprite.setTexture(texturas[0], true); // true para resetear el rect
    sprite.setColor(sf::Color::White); // Reiniciar color
}

void Estrella::recoger() {
    if (!recogida) {
        recogida = true;
        // Al recogerla, simplemente marcamos como recogida
        // y la animación terminada (para que desaparezca inmediatamente)
        animacionFinalizada = true;
    }
}

void Estrella::actualizar(float dt) {
    // Como ya no tenemos animación, este método es muy sencillo
    // No hacemos nada si la estrella no está recogida o ya terminó su animación
    
    // Si se recogió pero no ha terminado la animación (cosa que no debería suceder
    // ya que ahora cuando se recoge se marca como animación finalizada directamente)
    if (recogida && !animacionFinalizada) {
        // Simplemente marcar como terminada para que desaparezca
        animacionFinalizada = true;
    }
}

void Estrella::dibujar(sf::RenderWindow& ventana) {
    if (!animacionFinalizada) {
        ventana.draw(sprite);
    }
}

bool Estrella::contienePunto(const sf::Vector2f& punto) const {
    return sprite.getGlobalBounds().contains(punto);
}

bool Estrella::estaRecogida() const {
    return recogida;
}

bool Estrella::animacionTerminada() const {
    return animacionFinalizada;
}
