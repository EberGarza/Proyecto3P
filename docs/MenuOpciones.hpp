#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MenuOpciones {
public:
    enum class Resolucion {
        R800x600,
        R1024x768,
        R1280x720
    };

    MenuOpciones(sf::RenderWindow& win)
        : ventana(win), indice(0), resoluciones{
            {800, 600}, {1024, 768}, {1280, 720}
        }
    {
        items = {"800x600", "1024x768", "1280x720", "Volver"};
        fuente.loadFromFile("assets/fonts/VCR_OSD_MONO_1.001.ttf");
        for (size_t i = 0; i < items.size(); ++i) {
            sf::Text txt(items[i], fuente, 32);
            txt.setPosition(ventana.getSize().x / 2 - 80, 180 + i * 55);
            textos.push_back(txt);
        }
    }

    bool Mostrar(Resolucion& resolucionElegida) {
        while (ventana.isOpen()) {
            sf::Event ev;
            while (ventana.pollEvent(ev)) {
                if (ev.type == sf::Event::Closed) {
                    ventana.close();
                    return false;
                }
                if (ev.type == sf::Event::KeyPressed) {
                    if (ev.key.code == sf::Keyboard::W || ev.key.code == sf::Keyboard::Up) {
                        indice = (indice + items.size() - 1) % items.size();
                    } else if (ev.key.code == sf::Keyboard::S || ev.key.code == sf::Keyboard::Down) {
                        indice = (indice + 1) % items.size();
                    } else if (ev.key.code == sf::Keyboard::Enter) {
                        if (indice < 3) {
                            resolucionElegida = static_cast<Resolucion>(indice);
                            return true;
                        } else {
                            return false;
                        }
                    } else if (ev.key.code == sf::Keyboard::Escape) {
                        return false;
                    }
                }
            }
            ventana.clear(sf::Color(25, 25, 25));
            for (size_t i = 0; i < textos.size(); ++i) {
                // Eliminar tildes visuales correctamente
                std::string textoSinTilde = EliminarTildes(textos[i].getString());
                textos[i].setString(textoSinTilde);
                textos[i].setFillColor(i == indice ? sf::Color::Yellow : sf::Color::White);
                ventana.draw(textos[i]);
            }
            ventana.display();
        }
        return false;
    }

    sf::Vector2u ObtenerResolucion(Resolucion res) const {
        return resoluciones[static_cast<size_t>(res)];
    }

private:
    sf::RenderWindow& ventana;
    std::vector<std::string> items;
    std::vector<sf::Text> textos;
    sf::Font fuente;
    size_t indice;
    std::vector<sf::Vector2u> resoluciones;

    // Funcion auxiliar para eliminar tildes y eñes de un string UTF-8
    std::string EliminarTildes(const std::string& texto) {
        std::string resultado;
        for (size_t i = 0; i < texto.size(); ) {
            unsigned char c = texto[i];
            // Caracteres multibyte UTF-8 para vocales acentuadas y eñes
            if (c == 0xC3 && i + 1 < texto.size()) {
                unsigned char siguiente = texto[i + 1];
                switch (siguiente) {
                    case 0x81: resultado += 'A'; break; // Á
                    case 0xA1: resultado += 'a'; break; // á
                    case 0x89: resultado += 'E'; break; // É
                    case 0xA9: resultado += 'e'; break; // é
                    case 0x8D: resultado += 'I'; break; // Í
                    case 0xAD: resultado += 'i'; break; // í
                    case 0x93: resultado += 'O'; break; // Ó
                    case 0xB3: resultado += 'o'; break; // ó
                    case 0x9A: resultado += 'U'; break; // Ú
                    case 0xBA: resultado += 'u'; break; // ú
                    case 0x91: resultado += 'N'; break; // Ñ
                    case 0xB1: resultado += 'n'; break; // ñ
                    default:
                        // Si no es una tilde conocida, conservar ambos bytes
                        resultado += c;
                        resultado += siguiente;
                        break;
                }
                i += 2;
            } else {
                resultado += c;
                ++i;
            }
        }
        return resultado;
    }
};
