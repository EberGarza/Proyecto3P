// main.cpp - Punto de entrada para el juego
#include <SFML/Graphics.hpp>
#include <iostream>
#include "SplashScreen.hpp"
#include "Menu.hpp"
#include "Opciones.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cut the Rope");
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
            std::cout << "Iniciar juego (placeholder)" << std::endl;
        } else if (opcion == 1) {
            Opciones opciones(window);
            opciones.Mostrar();
        }
    }
    return 0;
}
