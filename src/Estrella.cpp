#include "Estrella.hpp"
#include <iostream>
#include <cmath> // Para usar sin()

Estrella::Estrella() :
    frameActual(0),
    tiempoAcumulado(0.0f),
    duracionFrame(0.1f), // 10 frames por segundo para la animación
    recogida(false),
    animacionFinalizada(false),
    tiempoEfecto(0.0f)
{
    // Cargar las texturas de la animación de la estrella
    texturas.resize(5); // Suponemos que hay 5 frames de animación
    
    // Cargar textura inicial
    if (!texturas[0].loadFromFile("assets/images/Star_Succesion_0.png")) {
        std::cerr << "Error al cargar la textura de la estrella: Star_Succesion_0.png" << std::endl;
    }
    
    // Cargar texturas de animación cuando se recoge
    if (!texturas[1].loadFromFile("assets/images/Star_Succesion_1.png")) {
        std::cerr << "Error al cargar la textura de la estrella: Star_Succesion_1.png" << std::endl;
    }
    
    if (!texturas[2].loadFromFile("assets/images/Star_Succesion_2.png")) {
        std::cerr << "Error al cargar la textura de la estrella: Star_Succesion_2.png" << std::endl;
    }
    
    if (!texturas[3].loadFromFile("assets/images/Star_Succesion_3.png")) {
        std::cerr << "Error al cargar la textura de la estrella: Star_Succesion_3.png" << std::endl;
    }
    
    // Quinta textura puede ser transparente o una variación final
    texturas[4] = texturas[3]; // Copiamos la última textura para el último frame
    
    // Configurar el sprite con la textura inicial
    sprite.setTexture(texturas[0]);
    
    // Centrar origen en el centro de la textura
    sf::Vector2u texSize = texturas[0].getSize();
    sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
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
    sprite.setTexture(texturas[0]);
    sprite.setColor(sf::Color::White); // Reiniciar color
}

void Estrella::recoger() {
    if (!recogida) {
        recogida = true;
        frameActual = 0;
        tiempoAcumulado = 0.0f;
    }
}

void Estrella::actualizar(float dt) {
    if (recogida && !animacionFinalizada) {
        tiempoAcumulado += dt;
        tiempoEfecto += dt;
        
        if (tiempoAcumulado >= duracionFrame) {
            tiempoAcumulado -= duracionFrame;
            frameActual++;
            
            if (frameActual < static_cast<int>(texturas.size())) {
                sprite.setTexture(texturas[frameActual]);
                
                // Obtener escala original
                float escalaOriginal = sprite.getScale().x;
                
                // Efecto de brillo y escala al ser recogida
                float escalaPulso = 1.0f + 0.2f * sin(tiempoEfecto * 10.0f);
                sprite.setScale(escalaOriginal * escalaPulso, escalaOriginal * escalaPulso);
                
                // Aumentar brillo gradualmente
                int brilloAdicional = static_cast<int>(127.0f * (float(frameActual) / texturas.size()));
                sf::Color color(
                    std::min(255, 255 - brilloAdicional),  // Menos rojo para que sea más brillante
                    std::min(255, 255),                    // Verde al máximo
                    std::min(255, 128 + brilloAdicional)   // Más azul para efecto brillante
                );
                sprite.setColor(color);
            } else {
                animacionFinalizada = true;
            }
        }
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
