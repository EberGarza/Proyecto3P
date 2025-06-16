// Opciones.cpp - Implementación del menú de opciones
// Archivo guardado en UTF-8 sin BOM
#ifdef _WIN32
#include <windows.h>
#endif
#include "Opciones.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

Opciones::Opciones(sf::RenderWindow& win) : ventana(win), seleccion(0), resolucionActual(0) {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Forzar salida UTF-8 en consola
    #endif
    // Forzar literal UTF-8 para la tilde
    items = {u8"Resolución", "Volver"};
    resoluciones = { {800, 600}, {1024, 768}, {1280, 720}, {1366, 768} };
    fuente.loadFromFile("assets/fonts/VCR_OSD_MONO_1.001.ttf");
    int fontSize = 36;
    int totalHeight = (int)items.size() * fontSize + ((int)items.size() - 1) * 30;
    int startY = (ventana.getSize().y - totalHeight) / 2;
    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text text(items[i], fuente, fontSize);
        text.setPosition(ventana.getSize().x / 2 - 120, startY + (int)i * (fontSize + 30));
        textos.push_back(text);
    }
}

void Opciones::Mostrar() {
    bool enOpciones = true;
    while (ventana.isOpen() && enOpciones) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                ventana.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                    seleccion = (seleccion + items.size() - 1) % items.size();
                } else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                    seleccion = (seleccion + 1) % items.size();
                } else if (event.key.code == sf::Keyboard::Enter) {
                    if (seleccion == 1) {
                        enOpciones = false; // Volver
                    } else if (seleccion == 0) {
                        ventana.create(sf::VideoMode(resoluciones[resolucionActual].x, resoluciones[resolucionActual].y), "Cut the Rope");
                        fuente.loadFromFile("assets/fonts/VCR_OSD_MONO_1.001.ttf");
                        textos.clear();
                        int fontSize = 36;
                        int totalHeight = (int)items.size() * fontSize + ((int)items.size() - 1) * 30;
                        int startY = (ventana.getSize().y - totalHeight) / 2;
                        for (size_t i = 0; i < items.size(); ++i) {
                            sf::Text text(items[i], fuente, fontSize);
                            text.setPosition(ventana.getSize().x / 2 - 120, startY + (int)i * (fontSize + 30));
                            textos.push_back(text);
                        }
                        // Pequeño delay para evitar doble enter
                        sf::sleep(sf::milliseconds(200));
                    }
                } else if (event.key.code == sf::Keyboard::Escape) {
                    enOpciones = false;
                } else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                    if (seleccion == 0) {
                        resolucionActual = (resolucionActual + resoluciones.size() - 1) % resoluciones.size();
                    }
                } else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                    if (seleccion == 0) {
                        resolucionActual = (resolucionActual + 1) % resoluciones.size();
                    }
                }
            }
        }
        // Mostrar flechas visuales en la opción de resolución
        if (!textos.empty()) {
            std::string resolStr = std::string(u8"Resolución: < ") + std::to_string(resoluciones[resolucionActual].x) + "x" + std::to_string(resoluciones[resolucionActual].y) + " >";
            textos[0].setString(resolStr);
            // Restaurar el texto de la opción 'Volver' por si fue sobrescrito
            if (textos.size() > 1) {
                textos[1].setString("Volver");
            }
        }
        ventana.clear(sf::Color(40, 40, 60));
        for (size_t i = 0; i < textos.size(); ++i) {
            textos[i].setFillColor(i == seleccion ? sf::Color::Yellow : sf::Color::White);
            ventana.draw(textos[i]);
        }
        ventana.display();
    }
}
