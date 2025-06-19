// MenuControles.cpp - Implementación de controles universales
#include "MenuControles.hpp"
#include <cstring>

TipoDispositivo MenuControles::tipo = TipoDispositivo::Teclado;
bool MenuControles::teclas[sf::Keyboard::KeyCount] = {false};
bool MenuControles::mouseBotones[sf::Mouse::ButtonCount] = {false};
bool MenuControles::gamepadBotones[sf::Joystick::ButtonCount] = {false};
float MenuControles::gamepadEjeX = 0.0f;
float MenuControles::gamepadEjeY = 0.0f;

void MenuControles::actualizar(const sf::Event& event) {
    if (tipo == TipoDispositivo::Teclado) {
        actualizarTeclado(event);
    }
    // Gamepad se actualiza por polling, no por evento
    if (tipo == TipoDispositivo::Gamepad) {
        actualizarGamepad();
    }
}

void MenuControles::actualizarTeclado(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code >= 0 && event.key.code < sf::Keyboard::KeyCount)
            teclas[event.key.code] = true;
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code >= 0 && event.key.code < sf::Keyboard::KeyCount)
            teclas[event.key.code] = false;
    }
}

void MenuControles::actualizarGamepad() {
    unsigned int id = 0; // Primer joystick
    if (sf::Joystick::isConnected(id)) {
        gamepadEjeX = sf::Joystick::getAxisPosition(id, sf::Joystick::X);
        gamepadEjeY = sf::Joystick::getAxisPosition(id, sf::Joystick::Y);
        for (unsigned int b = 0; b < sf::Joystick::getButtonCount(id); ++b) {
            gamepadBotones[b] = sf::Joystick::isButtonPressed(id, b);
        }
    }
}

bool MenuControles::Arriba() {
    if (tipo == TipoDispositivo::Teclado)
        return teclas[sf::Keyboard::W] || teclas[sf::Keyboard::Up];
    if (tipo == TipoDispositivo::Gamepad)
        return gamepadEjeY < -50.f;
    return false;
}

bool MenuControles::Abajo() {
    if (tipo == TipoDispositivo::Teclado)
        return teclas[sf::Keyboard::S] || teclas[sf::Keyboard::Down];
    if (tipo == TipoDispositivo::Gamepad)
        return gamepadEjeY > 50.f;
    return false;
}

bool MenuControles::Izquierda() {
    if (tipo == TipoDispositivo::Teclado)
        return teclas[sf::Keyboard::A] || teclas[sf::Keyboard::Left];
    if (tipo == TipoDispositivo::Gamepad)
        return gamepadEjeX < -50.f;
    return false;
}

bool MenuControles::Derecha() {
    if (tipo == TipoDispositivo::Teclado)
        return teclas[sf::Keyboard::D] || teclas[sf::Keyboard::Right];
    if (tipo == TipoDispositivo::Gamepad)
        return gamepadEjeX > 50.f;
    return false;
}

bool MenuControles::Aceptar() {
    if (tipo == TipoDispositivo::Teclado)
        return teclas[sf::Keyboard::Enter] || teclas[sf::Keyboard::Space] || sf::Mouse::isButtonPressed(sf::Mouse::Left);
    if (tipo == TipoDispositivo::Gamepad)
        return gamepadBotones[0]; // Botón A
    return false;
}

bool MenuControles::Cancelar() {
    if (tipo == TipoDispositivo::Teclado)
        return teclas[sf::Keyboard::Escape];
    if (tipo == TipoDispositivo::Gamepad)
        return gamepadBotones[1]; // Botón B
    return false;
}

sf::Vector2i MenuControles::mousePos(const sf::Window& ventana) {
    return sf::Mouse::getPosition(ventana);
}
