// 02_Tutorial.cpp - Logica del tutorial para Cut the Rope (version capibara)
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

class Tutorial {
public:
    Tutorial(sf::RenderWindow& win, sf::Font& font)
        : window(win), fuente(font) {}

    void Mostrar() {
        // Secuencia de mensajes para el tutorial (sin tildes)
        std::vector<std::string> mensajes = {
            "Bienvenido a Cut the Rope!",
            "Navega por los menus con W/S o las flechas.",
            "Selecciona usando Enter.",
            "Corta la cuerda con el raton para alimentar al personaje.",
            "Pulsa Escape si deseas saltar el tutorial."
        };
        std::vector<sf::Text> bloques;
        int tamanoLetra = 32;
        int altoTotal = (int)mensajes.size() * tamanoLetra + ((int)mensajes.size() - 1) * 18;
        int inicioY = (window.getSize().y - altoTotal) / 2;
        for (size_t i = 0; i < mensajes.size(); ++i) {
            sf::Text linea(mensajes[i], fuente, tamanoLetra);
            linea.setFillColor(sf::Color(230, 230, 255));
            linea.setPosition(window.getSize().x / 2 - linea.getLocalBounds().width / 2, inicioY + (int)i * (tamanoLetra + 18));
            bloques.push_back(linea);
        }
        bool mostrarOpcion = false;
        bool finalizar = false;
        while (window.isOpen() && !finalizar) {
            sf::Event ev;
            while (window.pollEvent(ev)) {
                if (ev.type == sf::Event::Closed) {
                    window.close();
                }
                if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape) {
                    mostrarOpcion = true;
                }
                if (mostrarOpcion && ev.type == sf::Event::KeyPressed) {
                    if (ev.key.code == sf::Keyboard::Y) {
                        finalizar = true;
                    } else if (ev.key.code == sf::Keyboard::N) {
                        mostrarOpcion = false;
                    }
                }
            }
            window.clear(sf::Color(35, 35, 60));
            for (auto& linea : bloques) window.draw(linea);
            if (mostrarOpcion) {
                sf::Text omitir("¿Deseas saltar el tutorial? (Y/N)", fuente, 28);
                omitir.setFillColor(sf::Color(255, 210, 0));
                omitir.setStyle(sf::Text::Bold);
                omitir.setPosition(window.getSize().x / 2 - omitir.getLocalBounds().width / 2, window.getSize().y - 70);
                window.draw(omitir);
            }
            window.display();
        }
    }
private:
    sf::RenderWindow& window;
    sf::Font& fuente;
};
