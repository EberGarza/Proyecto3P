// BotonesConfig.hpp - Configuración de botones para Cut the Rope
// Define las teclas y controles usados en el juego

#ifndef BOTONES_CONFIG_HPP
#define BOTONES_CONFIG_HPP

#include <SFML/Window/Keyboard.hpp>

struct BotonesConfig {
    sf::Keyboard::Key arriba = sf::Keyboard::W;
    sf::Keyboard::Key abajo = sf::Keyboard::S;
    sf::Keyboard::Key izquierda = sf::Keyboard::A;
    sf::Keyboard::Key derecha = sf::Keyboard::D;
    sf::Keyboard::Key aceptar = sf::Keyboard::Enter;
    sf::Keyboard::Key cancelar = sf::Keyboard::Escape; // Usado para menú de pausa
    // Puedes agregar más controles según lo necesites
};

#endif // BOTONES_CONFIG_HPP
