// Opciones.hpp - Declaración de la clase Opciones (menú de opciones)
#ifndef OPCIONES_HPP
#define OPCIONES_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Music.hpp"
#include "MusicButton.hpp"

class Opciones {
public:
    Opciones(sf::RenderWindow& win);
    void Mostrar();
private:
    sf::RenderWindow& ventana;
    std::vector<std::string> items;
    std::vector<sf::Text> textos;
    sf::Font fuente;
    int seleccion;
    std::vector<sf::Vector2u> resoluciones;
    int resolucionActual;
    // Nuevos miembros para assets
    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;
    sf::Texture figurasAnimTexture;
    sf::Sprite figurasAnimSprite;
    // Variables de animación
    float animX;
    float animY;
    float animVel;
    int animDirX;
    int animDirY;
    // Control de música
    Music music;
    MusicButton musicBtn;
    bool musicPlaying;
};

#endif // OPCIONES_HPP
