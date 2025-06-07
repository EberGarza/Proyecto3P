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

    void MostrarMenuInicio() {
        // Mostrar el menú de inicio usando SFML
        sf::RenderWindow window(sf::VideoMode(800, 600), "Cut the Rope - Menú de Inicio");
        sf::Texture menuTexture;
        // TODO: Añadir el asset real del menú de inicio en la ruta indicada
        if (!menuTexture.loadFromFile("assets/images/Menu_Inicio.png")) {
            std::cerr << "No se pudo cargar la imagen del menú de inicio. (Agrega el asset en assets/images/Menu_Inicio.png)" << std::endl;
            // Se puede mostrar un fondo simple como placeholder
        }
        sf::Sprite menuSprite(menuTexture);
        // Centrar la imagen
        sf::Vector2u size = menuTexture.getSize();
        menuSprite.setOrigin(size.x / 2, size.y / 2);
        menuSprite.setPosition(400, 300);
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                // Lógica para botones, teclas, etc.
            }
            window.clear(sf::Color(50, 50, 50)); // Fondo gris oscuro
            if (size.x > 0 && size.y > 0) {
                window.draw(menuSprite);
            }
            // Aquí puedes dibujar texto o botones adicionales
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
