// Opciones.cpp - Implementación del menú de opciones
// Archivo guardado en UTF-8 sin BOM
#ifdef _WIN32
#include <windows.h>
#endif
#include "Opciones.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

Opciones::Opciones(sf::RenderWindow& win) : ventana(win), seleccion(0), resolucionActual(0), animX(0.f), animY(0.f), animVel(0.015f), animDirX(1), animDirY(1) {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Forzar salida UTF-8 en consola
    #endif
    items = {u8"Resolución", "Volver"};
    resoluciones = { {800, 600}, {1024, 768}, {1280, 720}, {1366, 768} };
    fuente.loadFromFile("assets/fonts/VCR_OSD_MONO_1.001.ttf");
    fondoTexture.loadFromFile("assets/images/Fondo_Opciones.png");
    fondoSprite.setTexture(fondoTexture);
    figurasAnimTexture.loadFromFile("assets/images/Figuras_Anim.png");
    figurasAnimSprite.setTexture(figurasAnimTexture);
    // El escalado se ajustará dinámicamente en Mostrar()
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
    // Crear el título del menú de opciones
    sf::Text titulo;
    titulo.setFont(fuente);
    titulo.setString("OPCIONES");
    titulo.setCharacterSize(48);
    titulo.setFillColor(sf::Color(255, 220, 80));
    // Centrar horizontalmente y colocar en la parte superior
    sf::FloatRect bounds = titulo.getLocalBounds();
    titulo.setOrigin(bounds.width / 2, bounds.height / 2);
    titulo.setPosition(ventana.getSize().x / 2, 60);
    titulo.setRotation(-8.f); // Ángulo ligero para realce

    bool enOpciones = true;
    float rangoX = ventana.getSize().x * 0.20f; // 20% del ancho
    float rangoY = ventana.getSize().y * 0.10f; // 10% del alto
    float centroX = ventana.getSize().x / 2.f;
    float centroY = ventana.getSize().y / 2.f;
    float maxScaleX = (ventana.getSize().x * 0.18f) / figurasAnimTexture.getSize().x;
    float maxScaleY = (ventana.getSize().y * 0.18f) / figurasAnimTexture.getSize().y;
    float scale = std::min(maxScaleX, maxScaleY);
    if (scale > 1.0f) scale = 1.0f;
    if (scale < 0.25f) scale = 0.25f;
    figurasAnimSprite.setScale(scale, scale);
    sf::Vector2f spriteSize(figurasAnimSprite.getGlobalBounds().width, figurasAnimSprite.getGlobalBounds().height);
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
            if (textos.size() > 1) {
                textos[1].setString("Volver");
            }
        }
        // Animación diagonal y muy lenta, centrada
        animX += animVel * animDirX;
        animY += animVel * animDirY;
        if (animX > rangoX) animDirX = -1;
        if (animX < -rangoX) animDirX = 1;
        if (animY > rangoY) animDirY = -1;
        if (animY < -rangoY) animDirY = 1;
        // Efecto infinito: dibujar varias instancias para cubrir el área
        ventana.clear();
        ventana.draw(fondoSprite);
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                float posX = centroX - spriteSize.x/2 + animX + dx * spriteSize.x;
                float posY = centroY - spriteSize.y/2 + animY + dy * spriteSize.y;
                figurasAnimSprite.setPosition(posX, posY);
                ventana.draw(figurasAnimSprite);
            }
        }
        ventana.draw(titulo);
        for (size_t i = 0; i < textos.size(); ++i) {
            textos[i].setFillColor(i == seleccion ? sf::Color::Yellow : sf::Color::White);
            ventana.draw(textos[i]);
        }
        ventana.display();
    }
}
