// Controles.hpp - Gestión centralizada de controles universales
#ifndef CONTROLES_HPP
#define CONTROLES_HPP
#include <SFML/Window.hpp>

class Controles {
public:
    // Actualiza el estado de los controles (debe llamarse cada frame con el evento)
    static void actualizar(const sf::Event& event);
    // Consulta si una tecla está presionada
    static bool teclaPresionada(sf::Keyboard::Key key);
    // Consulta si el mouse está presionado
    static bool mousePresionado(sf::Mouse::Button boton);
    // Posición actual del mouse en la ventana
    static sf::Vector2i mousePos(const sf::Window& ventana);
    // Estados específicos para WSAD
    static bool W();
    static bool S();
    static bool A();
    static bool D();
private:
    static bool teclas[sf::Keyboard::KeyCount];
    static bool mouseBotones[sf::Mouse::ButtonCount];
};

#endif // CONTROLES_HPP
