// MenuOpciones.hpp - Declaración de la clase MenuOpciones (menú de opciones)
#ifndef MENUOPCIONES_HPP
#define MENUOPCIONES_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Music.hpp"
#include "MusicButton.hpp"

class MenuOpciones {
public:
    MenuOpciones(sf::RenderWindow& win);
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

#endif // MENUOPCIONES_HPP
