// MenuControles.hpp - Gestión de controles para el menú
#ifndef MENU_CONTROLES_HPP
#define MENU_CONTROLES_HPP
#include <SFML/Window.hpp>
#include <SFML/Window/Joystick.hpp>

// Enumeración para tipo de dispositivo
enum class TipoDispositivo {
    Teclado,
    Gamepad
};

class MenuControles {
public:
    static TipoDispositivo tipo;
    // Métodos para actualizar el estado de los controles
    static void actualizar(const sf::Event& event);
    // Métodos de consulta unificados
    static bool Arriba();
    static bool Abajo();
    static bool Izquierda();
    static bool Derecha();
    static bool Aceptar(); // Ejemplo: Enter o botón A
    static bool Cancelar(); // Ejemplo: Escape o botón B
    static sf::Vector2i mousePos(const sf::Window& ventana);
private:
    static bool teclas[sf::Keyboard::KeyCount];
    static bool mouseBotones[sf::Mouse::ButtonCount];
    static bool gamepadBotones[sf::Joystick::ButtonCount];
    static float gamepadEjeX;
    static float gamepadEjeY;
    static void actualizarTeclado(const sf::Event& event);
    static void actualizarGamepad();
};

#endif // MENU_CONTROLES_HPP
