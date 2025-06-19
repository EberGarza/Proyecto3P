// Menu.cpp - Implementación del menú principal
#include "Menu.hpp"
#include "MenuControles.hpp"
#include "MusicButton.hpp"
#include "Music.hpp"
#include <SFML/Graphics.hpp>
#include <iostream> // Incluir iostream para std::cerr

Menu::Menu(sf::RenderWindow& win) : ventana(win), seleccion(0) {
    opciones = {"Jugar", "Opciones", "Salir"};
    fuente.loadFromFile("assets/fonts/VCR_OSD_MONO_1.001.ttf");
    int fontSize = 40;
    int totalHeight = (int)opciones.size() * fontSize + ((int)opciones.size() - 1) * 30;
    int startY = (ventana.getSize().y - totalHeight) / 2;
    for (size_t i = 0; i < opciones.size(); ++i) {
        sf::Text text(opciones[i], fuente, fontSize);
        text.setPosition(ventana.getSize().x / 2 - 80, startY + (int)i * (fontSize + 30));
        textosMenu.push_back(text);
    }
}

OpcionMenu Menu::Mostrar() {
    // Cargar imagen de fondo
    sf::Texture fondoTexture;
    bool fondoCargado = fondoTexture.loadFromFile("assets/images/Menu_Principal.png");
    sf::Sprite fondoSprite;
    if (fondoCargado) {
        fondoSprite.setTexture(fondoTexture);
        sf::Vector2u sizeImg = fondoTexture.getSize();
        sf::Vector2u sizeWin = ventana.getSize();
        float scaleX = static_cast<float>(sizeWin.x) / sizeImg.x;
        float scaleY = static_cast<float>(sizeWin.y) / sizeImg.y;
        fondoSprite.setScale(scaleX, scaleY);
    }
    // Título del juego
    sf::Text titulo;
    titulo.setFont(fuente);
    titulo.setString("CUT THE ROPE");
    titulo.setCharacterSize(56);
    titulo.setFillColor(sf::Color(255, 220, 80));
    sf::FloatRect bounds = titulo.getLocalBounds();
    titulo.setOrigin(bounds.width / 2, bounds.height / 2);
    titulo.setPosition(ventana.getSize().x / 2, 80);
    titulo.setRotation(-8.f);

    Music music;
    if (!music.load("assets/audio/Menu.ogg")) {
        std::cerr << "[ERROR] No se pudo cargar el archivo de música: assets/audio/Menu.ogg\n";
    }
    MusicButton musicBtn;
    bool musicPlaying = false;

    while (ventana.isOpen()) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            MenuControles::actualizar(event);
            if (event.type == sf::Event::Closed) {
                return SALIR; // Salir
            }
            if (event.type == sf::Event::KeyPressed) {
                // Cambiar referencias WASD a Arriba, Abajo, Izquierda, Derecha, Aceptar, Cancelar
                if (MenuControles::Arriba()) {
                    seleccion = (seleccion + opciones.size() - 1) % opciones.size();
                } else if (MenuControles::Abajo()) {
                    seleccion = (seleccion + 1) % opciones.size();
                } else if (MenuControles::Aceptar()) {
                    return static_cast<OpcionMenu>(seleccion);
                } else if (MenuControles::Cancelar()) {
                    return SALIR; // Salir
                }
            }
        }
        ventana.clear(sf::Color(30, 30, 30));
        if (fondoCargado) {
            ventana.draw(fondoSprite);
        }
        ventana.draw(titulo); // Dibujar el título primero
        for (size_t i = 0; i < textosMenu.size(); ++i) {
            textosMenu[i].setFillColor(i == seleccion ? sf::Color::Yellow : sf::Color::White);
            ventana.draw(textosMenu[i]);
        }
        // Detectar selección con mouse
        for (size_t i = 0; i < textosMenu.size(); ++i) {
            auto bounds = textosMenu[i].getGlobalBounds();
            sf::Vector2i mouse = MenuControles::mousePos(ventana);
            if (bounds.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
                textosMenu[i].setFillColor(sf::Color(255, 255, 120)); // Resalta
                // Reemplazar mousePresionado por Aceptar para clicks principales
                if (MenuControles::Aceptar()) {
                    return static_cast<OpcionMenu>(i);
                }
            } else {
                textosMenu[i].setFillColor(sf::Color(255, 255, 255));
            }
        }
        // Dibuja el botón de música
        musicBtn.draw(ventana);
        // Detecta click en el botón
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mouse = sf::Mouse::getPosition(ventana);
            if (musicBtn.isClicked(mouse)) {
                if (musicPlaying) {
                    music.pause();
                    musicPlaying = false;
                } else {
                    music.play();
                    musicPlaying = true;
                }
                // Espera a que se suelte el botón para evitar múltiples toggles
                while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}
            }
        }
        ventana.display();
    }
    return SALIR; // Si la ventana se cierra
}
