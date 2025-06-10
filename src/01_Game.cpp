// 01_Game.cpp - Estructura base de la clase Game para Cut the Rope (versión capibara)
// Archivo base para la implementación inicial del núcleo del juego.

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../docs/BotonesConfig.hpp"
#include "../docs/MenuOpciones.hpp"
#include <thread>
#include <chrono>
#include "02_Tutorial.cpp"

// Clase principal que controla el flujo del juego
class Game {
public:
    Game() : state(GameState::Splash), window(sf::VideoMode(1024, 768), "Cut the Rope") {
    }

    void Inicializar() {
        // Inicializar componentes del juego
    }

    void MostrarSplashScreen() {
        sf::Texture texturaSplash;
        if (!texturaSplash.loadFromFile("assets/images/Splash_Screen.png")) {
            std::cerr << "No se pudo cargar la imagen de splash screen." << std::endl;
            return;
        }
        sf::Sprite spriteSplash(texturaSplash);
        sf::Vector2u sizeImg = texturaSplash.getSize();
        sf::Vector2u sizeWin = window.getSize();
        float scaleX = static_cast<float>(sizeWin.x) / sizeImg.x;
        float scaleY = static_cast<float>(sizeWin.y) / sizeImg.y;
        // Escalado proporcional para evitar estiramientos
        float scale = std::min(scaleX, scaleY);
        spriteSplash.setScale(scale, scale);
        // Centrar la imagen
        spriteSplash.setOrigin(sizeImg.x / 2.f, sizeImg.y / 2.f);
        spriteSplash.setPosition(sizeWin.x / 2.f, sizeWin.y / 2.f);
        sf::Clock relojGeneral;
        sf::Clock relojFrame;
        float opacidad = 0.f;
        bool entrando = true;
        bool saliendo = false;
        float velocidadTransicion = 255.f / 0.8f;
        bool splashActiva = true;
        bool cerrarVentana = false;
        while (window.isOpen() && splashActiva) {
            float tiempoFrame = relojFrame.restart().asSeconds();
            sf::Event evento;
            while (window.pollEvent(evento)) {
                if (!saliendo && (evento.type == sf::Event::Closed)) {
                    cerrarVentana = true;
                    splashActiva = false;
                    break;
                }
                if (!saliendo && (evento.type == sf::Event::KeyPressed || evento.type == sf::Event::MouseButtonPressed)) {
                    saliendo = true;
                    entrando = false;
                }
            }
            if (cerrarVentana) break;
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
                    splashActiva = false;
                }
            }
            spriteSplash.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(opacidad)));
            window.clear(sf::Color::Black); // Fondo negro (barras si sobra espacio)
            window.draw(spriteSplash);
            window.display();
        }
        if (cerrarVentana) {
            state = GameState::Exit;
            window.close();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

    void MostrarMenuPrincipal() {
        BotonesConfig botones;
        window.setTitle("Cut the Rope");
        sf::Font font;
        if (!font.loadFromFile("assets/fonts/VCR_OSD_MONO_1.001.ttf")) {
            if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
                return;
            }
        }
        sf::Texture fondoTexture;
        bool fondoCargado = fondoTexture.loadFromFile("assets/images/Menu_Principal.png");
        sf::Sprite fondoSprite;
        if (fondoCargado) {
            fondoSprite.setTexture(fondoTexture);
            // Escalado automático del fondo a la resolución de la ventana
            sf::Vector2u sizeImg = fondoTexture.getSize();
            sf::Vector2u sizeWin = window.getSize();
            float scaleX = static_cast<float>(sizeWin.x) / sizeImg.x;
            float scaleY = static_cast<float>(sizeWin.y) / sizeImg.y;
            fondoSprite.setScale(scaleX, scaleY);
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
        // Titulo principal y subtitulo adaptativos
        sf::Font fontTitulo;
        if (!fontTitulo.loadFromFile("assets/fonts/04B_30__.TTF")) {
            fontTitulo = font;
        }
        // Tamaño adaptativo segun resolucion
        int anchoVentana = window.getSize().x;
        int altoVentana = window.getSize().y;
        int tamTitulo = std::max(40, anchoVentana / 16);
        int tamSub = std::max(22, anchoVentana / 32);
        // Titulo superior
        sf::Text tituloPrincipal("Cut the Rope", fontTitulo, tamTitulo);
        tituloPrincipal.setFillColor(sf::Color(0, 200, 255));
        tituloPrincipal.setStyle(sf::Text::Bold);
        float xTitulo = (anchoVentana - tituloPrincipal.getLocalBounds().width) / 2.f;
        float yTitulo = std::max(10.f, altoVentana * 0.07f);
        tituloPrincipal.setPosition(xTitulo, yTitulo);
        // Subtitulo inferior con angulo
        sf::Text subtitulo("Capibara Edition", fontTitulo, tamSub);
        subtitulo.setFillColor(sf::Color(255, 180, 0));
        subtitulo.setStyle(sf::Text::Italic);
        float xSub = (anchoVentana - subtitulo.getLocalBounds().width) / 2.f;
        float ySub = altoVentana * 0.17f + tituloPrincipal.getLocalBounds().height;
        subtitulo.setPosition(xSub, ySub);
        subtitulo.setRotation(-7.f);

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
                            Tutorial tutorial(window, font);
                            tutorial.Mostrar();
                            state = GameState::Playing;
                        } else if (seleccion == 1) {
                            MenuOpciones opcionesMenu(window);
                            MenuOpciones::Resolucion resolSel;
                            if (opcionesMenu.Mostrar(resolSel)) {
                                sf::Vector2u nuevaRes = opcionesMenu.ObtenerResolucion(resolSel);
                                window.create(sf::VideoMode(nuevaRes.x, nuevaRes.y), "Cut the Rope");
                                if (fondoCargado) {
                                    sf::Vector2u sizeImg = fondoTexture.getSize();
                                    sf::Vector2u sizeWin = window.getSize();
                                    float scaleX = static_cast<float>(sizeWin.x) / sizeImg.x;
                                    float scaleY = static_cast<float>(sizeWin.y) / sizeImg.y;
                                    fondoSprite.setScale(scaleX, scaleY);
                                }
                                int totalHeight = (int)opciones.size() * fontSize + ((int)opciones.size() - 1) * 30;
                                int startY = (window.getSize().y - totalHeight) / 2;
                                for (size_t i = 0; i < textosMenu.size(); ++i) {
                                    textosMenu[i].setPosition(window.getSize().x / 2 - 80, startY + (int)i * (fontSize + 30));
                                }
                                // Reposicionar titulos tras cambio de resolucion
                                int anchoVentana = window.getSize().x;
                                int altoVentana = window.getSize().y;
                                int tamTitulo = std::max(40, anchoVentana / 16);
                                int tamSub = std::max(22, anchoVentana / 32);
                                tituloPrincipal.setCharacterSize(tamTitulo);
                                float xTitulo = (anchoVentana - tituloPrincipal.getLocalBounds().width) / 2.f;
                                float yTitulo = std::max(10.f, altoVentana * 0.07f);
                                tituloPrincipal.setPosition(xTitulo, yTitulo);
                                subtitulo.setCharacterSize(tamSub);
                                float xSub = (anchoVentana - subtitulo.getLocalBounds().width) / 2.f;
                                float ySub = altoVentana * 0.17f + tituloPrincipal.getLocalBounds().height;
                                subtitulo.setPosition(xSub, ySub);
                            }
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
            window.draw(tituloPrincipal);
            window.draw(subtitulo);
            for (size_t i = 0; i < textosMenu.size(); ++i) {
                // Eliminar tildes visuales
                std::string textoSinTilde = textosMenu[i].getString();
                for (char& c : textoSinTilde) {
                    if (c == '\xC1' || c == '\xE1') c = 'a';
                    if (c == '\xC9' || c == '\xE9') c = 'e';
                    if (c == '\xCD' || c == '\xED') c = 'i';
                    if (c == '\xD3' || c == '\xF3') c = 'o';
                    if (c == '\xDA' || c == '\xFA') c = 'u';
                    if (c == '\xD1' || c == '\xF1') c = 'n';
                }
                textosMenu[i].setString(textoSinTilde);
                textosMenu[i].setFillColor(i == seleccion ? sf::Color::Yellow : sf::Color::White);
                window.draw(textosMenu[i]);
            }
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
        bool splashMostrada = false;
        while (state != GameState::Exit && window.isOpen()) {
            switch (state) {
                case GameState::Splash:
                    if (!splashMostrada) {
                        MostrarSplashScreen();
                        splashMostrada = true;
                        if (!window.isOpen()) {
                            state = GameState::Exit;
                            break;
                        }
                        state = GameState::Menu;
                    } else {
                        state = GameState::Menu;
                    }
                    break;
                case GameState::Menu:
                    MostrarMenuPrincipal();
                    if (!window.isOpen()) state = GameState::Exit;
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
