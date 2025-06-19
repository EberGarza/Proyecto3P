// Menu.hpp - Clase para el menú principal
#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum OpcionMenu {
    JUGAR = 0,
    OPCIONES,
    SALIR
};

class Menu {
public:
    Menu(sf::RenderWindow& win);
    OpcionMenu Mostrar();
private:
    sf::RenderWindow& ventana;
    std::vector<std::string> opciones;
    std::vector<sf::Text> textosMenu;
    sf::Font fuente;
    int seleccion;
};

#endif // MENU_HPP
