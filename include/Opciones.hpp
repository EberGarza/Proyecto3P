// Opciones.hpp - Declaración de la clase Opciones (menú de opciones)
#ifndef OPCIONES_HPP
#define OPCIONES_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

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
};

#endif // OPCIONES_HPP
