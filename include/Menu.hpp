// Menu.hpp - Clase para el menú principal
#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(sf::RenderWindow& win);
    int Mostrar(); // Devuelve 0: Jugar, 1: Opciones, 2: Salir
private:
    sf::RenderWindow& ventana;
    std::vector<std::string> opciones;
    std::vector<sf::Text> textosMenu;
    sf::Font fuente;
    int seleccion;
};

#endif // MENU_HPP
