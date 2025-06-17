// Controles.cpp - Implementación de controles universales
#include "Controles.hpp"
#include <cstring>

bool Controles::teclas[sf::Keyboard::KeyCount] = {false};
bool Controles::mouseBotones[sf::Mouse::ButtonCount] = {false};

void Controles::actualizar(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code >= 0 && event.key.code < sf::Keyboard::KeyCount)
            teclas[event.key.code] = true;
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code >= 0 && event.key.code < sf::Keyboard::KeyCount)
            teclas[event.key.code] = false;
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button >= 0 && event.mouseButton.button < sf::Mouse::ButtonCount)
            mouseBotones[event.mouseButton.button] = true;
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button >= 0 && event.mouseButton.button < sf::Mouse::ButtonCount)
            mouseBotones[event.mouseButton.button] = false;
    }
}

bool Controles::teclaPresionada(sf::Keyboard::Key key) {
    return teclas[key];
}

bool Controles::mousePresionado(sf::Mouse::Button boton) {
    return mouseBotones[boton];
}

sf::Vector2i Controles::mousePos(const sf::Window& ventana) {
    return sf::Mouse::getPosition(ventana);
}

bool Controles::W() { return teclas[sf::Keyboard::W]; }
bool Controles::S() { return teclas[sf::Keyboard::S]; }
bool Controles::A() { return teclas[sf::Keyboard::A]; }
bool Controles::D() { return teclas[sf::Keyboard::D]; }
