// SplashScreen.cpp - Implementación de la clase SplashScreen
#include "SplashScreen.hpp"
#include "Controles.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void SplashScreen::Mostrar(sf::RenderWindow& window) {
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
    float scale = std::min(scaleX, scaleY);
    spriteSplash.setScale(scale, scale);
    spriteSplash.setOrigin(sizeImg.x / 2.f, sizeImg.y / 2.f);
    spriteSplash.setPosition(sizeWin.x / 2.f, sizeWin.y / 2.f);

    float opacidad = 0.f;
    float duracionTransicion = 1.0f; // segundos
    float duracionSplash = 1.0f; // tiempo visible total (sin transiciones)
    sf::Clock reloj;
    enum class Estado { FadeIn, Visible, FadeOut };
    Estado estado = Estado::FadeIn;
    bool salir = false;

    while (window.isOpen() && !salir) {
        sf::Event event;
        while (window.pollEvent(event)) {
            Controles::actualizar(event);
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
                if (estado == Estado::Visible) {
                    estado = Estado::FadeOut;
                    reloj.restart();
                }
            }
        }
        float t = reloj.getElapsedTime().asSeconds();
        switch (estado) {
            case Estado::FadeIn:
                opacidad = std::min(255.f, 255.f * (t / duracionTransicion));
                if (t >= duracionTransicion) {
                    estado = Estado::Visible;
                    reloj.restart();
                }
                break;
            case Estado::Visible:
                opacidad = 255.f;
                if (t >= duracionSplash) {
                    estado = Estado::FadeOut;
                    reloj.restart();
                }
                break;
            case Estado::FadeOut:
                opacidad = std::max(0.f, 255.f * (1.f - t / duracionTransicion));
                if (t >= duracionTransicion) {
                    salir = true;
                }
                break;
        }
        spriteSplash.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(opacidad)));
        window.clear(sf::Color::Black);
        window.draw(spriteSplash);
        window.display();
    }
}
