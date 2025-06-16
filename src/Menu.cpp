// Menu.cpp - Implementación del menú principal
#include "Menu.hpp"
#include <SFML/Graphics.hpp>

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

int Menu::Mostrar() {
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
    while (ventana.isOpen()) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return 2; // Salir
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                    seleccion = (seleccion + opciones.size() - 1) % opciones.size();
                } else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                    seleccion = (seleccion + 1) % opciones.size();
                } else if (event.key.code == sf::Keyboard::Enter) {
                    return seleccion;
                } else if (event.key.code == sf::Keyboard::Escape) {
                    return 2; // Salir
                }
            }
        }
        ventana.clear(sf::Color(30, 30, 30));
        if (fondoCargado) {
            ventana.draw(fondoSprite);
        }
        for (size_t i = 0; i < textosMenu.size(); ++i) {
            textosMenu[i].setFillColor(i == seleccion ? sf::Color::Yellow : sf::Color::White);
            ventana.draw(textosMenu[i]);
        }
        ventana.display();
    }
    return 2; // Si la ventana se cierra
}
