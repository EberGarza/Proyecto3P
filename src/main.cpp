// main.cpp - Punto de entrada para el juego
#include <SFML/Graphics.hpp>
#include <iostream>
#include "SplashScreen.hpp"
#include "Menu.hpp"
#include "Opciones.hpp"
#include "Tutorial.hpp"
#include "Rope.hpp"
#include "Cake.hpp"
#include "MenuControles.hpp"
#include "AlertaAnim.hpp"
#include "Plataforma.hpp"
#include "Victoria.hpp"

int main() {
    // Iniciar en pantalla completa para observar mejor la interacción de los objetos
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Cut the Rope", sf::Style::Fullscreen);
    bool running = true;
    bool splashMostrado = false;
    while (running && window.isOpen()) {
        if (!splashMostrado) {
            SplashScreen splash;
            splash.Mostrar(window);
            splashMostrado = true;
        }
        Menu menu(window);
        int opcion = menu.Mostrar();
        if (opcion == 2) { // Salir
            running = false;
        } else if (opcion == 0) {
            // Iniciar tutorial
            Tutorial tutorial(window);
            tutorial.Ejecutar();
        } else if (opcion == 1) {
            Opciones opciones(window);
            opciones.Mostrar();
        }
    }
    return 0;
}
