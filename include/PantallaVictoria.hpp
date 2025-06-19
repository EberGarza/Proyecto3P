#ifndef PANTALLA_VICTORIA_HPP
#define PANTALLA_VICTORIA_HPP

#include <SFML/Graphics.hpp>
#include <string>

class PantallaVictoria {
public:
    PantallaVictoria(sf::RenderWindow& window);
    void mostrar();
    void setEstrellasRecogidas(int estrellas) { estrellasRecogidas = estrellas; }
    
private:
    sf::RenderWindow& ventana;
    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;
    sf::Font fuente;
    sf::Text titulo;
    sf::Text mensaje;
    sf::Text instruccion;
    sf::Text textoEstrellas;
    
    int estrellasRecogidas = 0;
    int totalEstrellas = 3;
    
    // Efecto para los textos
    float tiempoEfecto;
    float velocidadEfecto;
};

#endif // PANTALLA_VICTORIA_HPP
