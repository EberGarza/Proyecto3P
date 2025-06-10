// 01_Game.cpp - Estructura base de la clase Game para Cut the Rope (versión capibara)
// Archivo base para la implementación inicial del núcleo del juego.

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../docs/BotonesConfig.hpp"
#include <thread>
#include <chrono>

// Clase principal que controla el flujo del juego
class Game {
public:
    Game() : state(GameState::Splash), window(sf::VideoMode(1024, 768), "Cut the Rope") {
    }

    void Inicializar() {
        // Inicializar componentes del juego
    }

    void MostrarSplashScreen() {
        // Usar la ventana principal en vez de crear una nueva
        sf::Texture texturaSplash;
        if (!texturaSplash.loadFromFile("assets/images/Splash_Screen.png")) {
            std::cerr << "No se pudo cargar la imagen de splash screen." << std::endl;
            return;
        }
        sf::Sprite spriteSplash(texturaSplash);
        sf::Vector2u dimensiones = texturaSplash.getSize();
        spriteSplash.setOrigin(dimensiones.x / 2, dimensiones.y / 2);
        spriteSplash.setPosition(window.getSize().x / 2, window.getSize().y / 2);
        sf::Clock relojGeneral;
        sf::Clock relojFrame;
        float opacidad = 0.f;
        bool entrando = true;
        bool saliendo = false;
        float velocidadTransicion = 255.f / 0.8f;
        while (true) {
            float tiempoFrame = relojFrame.restart().asSeconds();
            sf::Event evento;
            while (window.pollEvent(evento)) {
                if (evento.type == sf::Event::Closed || evento.type == sf::Event::KeyPressed || evento.type == sf::Event::MouseButtonPressed) {
                    saliendo = true;
                    entrando = false;
                }
            }
            float transcurrido = relojGeneral.getElapsedTime().asSeconds();
            if (entrando) {
                opacidad += velocidadTransicion * tiempoFrame;
                if (opacidad >= 255.f) {
                    opacidad = 255.f;
                    entrando = false;
                }
            } else if (!saliendo && transcurrido > 2.0f) {
                saliendo = true;
            }
            if (saliendo) {
                opacidad -= velocidadTransicion * tiempoFrame;
                if (opacidad <= 0.f) {
                    opacidad = 0.f;
                    break;
                }
            }
            spriteSplash.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(opacidad)));
            window.clear(sf::Color::Black);
            window.draw(spriteSplash);
            window.display();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void MostrarMenuPrincipal() {
        BotonesConfig botones;
        // Usar la ventana principal, no crear una nueva
        window.setTitle("Cut the Rope");
        sf::Font font;
        if (!font.loadFromFile("assets/fonts/VCR_OSD_MONO_1.001.ttf")) {
            if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
                return;
            }
        }
        sf::Texture fondoTexture;
        bool fondoCargado = fondoTexture.loadFromFile("assets/images/Menu_Principal.jpg");
        sf::Sprite fondoSprite;
        if (fondoCargado) {
            fondoSprite.setTexture(fondoTexture);
        }
        std::vector<std::string> opciones = {"Jugar", "Opciones", "Salir"};
        std::vector<sf::Text> textosMenu;
        int fontSize = 40;
        int totalHeight = (int)opciones.size() * fontSize + ((int)opciones.size() - 1) * 30;
        int startY = (window.getSize().y - totalHeight) / 2;
        for (size_t i = 0; i < opciones.size(); ++i) {
            sf::Text text(opciones[i], font, fontSize);
            text.setPosition(window.getSize().x / 2 - 80, startY + (int)i * (fontSize + 30));
            textosMenu.push_back(text);
        }
        int seleccion = 0;
        while (window.isOpen() && state == GameState::Menu) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    state = GameState::Exit;
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == botones.arriba) {
                        seleccion = (seleccion + opciones.size() - 1) % opciones.size();
                    } else if (event.key.code == botones.abajo) {
                        seleccion = (seleccion + 1) % opciones.size();
                    } else if (event.key.code == botones.aceptar) {
                        if (seleccion == 0) {
                            state = GameState::Playing;
                        } else if (seleccion == 1) {
                            // Opciones futuras
                        } else if (seleccion == 2) {
                            state = GameState::Exit;
                            window.close();
                        }
                    } else if (event.key.code == botones.cancelar) {
                        state = GameState::Exit;
                        window.close();
                    }
                }
            }
            window.clear(sf::Color(30, 30, 30));
            if (fondoCargado) {
                window.draw(fondoSprite);
            }
            for (size_t i = 0; i < textosMenu.size(); ++i) {
                textosMenu[i].setFillColor(i == seleccion ? sf::Color::Yellow : sf::Color::White);
                window.draw(textosMenu[i]);
            }
            window.display();
        }
    }

    void BuclePrincipal() {
        while (state != GameState::Exit && window.isOpen()) {
            switch (state) {
                case GameState::Splash:
                    MostrarSplashScreen();
                    state = GameState::Menu;
                    break;
                case GameState::Menu:
                    MostrarMenuPrincipal();
                    break;
                case GameState::Playing:
                    // Aquí iría la lógica del juego principal
                    // Simulación de juego, luego regresa al menú
                    state = GameState::Menu;
                    break;
                case GameState::Exit:
                    break;
            }
        }
    }

private:
    enum class GameState {
        Splash,
        Menu,
        Playing,
        Exit
    };

    GameState state;
    sf::RenderWindow window;
};

// Archivo base para expandir la lógica de la clase Game.
