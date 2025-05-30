// 01_Game.cpp - Estructura base de la clase Game para Cut the Rope (versión capibara)
// Archivo base para la implementación inicial del núcleo del juego.

#include <iostream>
#include <SFML/Graphics.hpp>

// Clase principal que controla el flujo del juego
class Game {
public:
    Game() {
        // Constructor: inicialización de variables y recursos
        std::cout << "[Game] Inicializando juego..." << std::endl;
    }

    void Inicializar() {
        // Inicializar componentes del juego
        std::cout << "[Game] Componentes inicializados." << std::endl;
    }

    void MostrarSplashScreen() {
        // Mostrar la Splash Screen usando SFML
        sf::RenderWindow window(sf::VideoMode(800, 600), "Cut the Rope - Splash Screen");
        sf::Texture splashTexture;
        if (!splashTexture.loadFromFile("assets/images/Splash_Screen.png")) {
            std::cerr << "No se pudo cargar la imagen de splash screen." << std::endl;
            return;
        }
        sf::Sprite splashSprite(splashTexture);
        // Centrar la imagen
        sf::Vector2u size = splashTexture.getSize();
        splashSprite.setOrigin(size.x / 2, size.y / 2);
        splashSprite.setPosition(400, 300);
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
                    window.close();
                }
            }
            window.clear(sf::Color::Black);
            window.draw(splashSprite);
            window.display();
        }
    }

    void BuclePrincipal() {
        // Bucle principal del juego
        std::cout << "[Game] Iniciando bucle principal..." << std::endl;
        // Aquí iría la lógica de actualización y renderizado
    }
};

// Archivo base para expandir la lógica de la clase Game.
