// Tutorial.hpp - Declaración de la clase Tutorial para el primer nivel
#ifndef TUTORIAL_HPP
#define TUTORIAL_HPP
#include <SFML/Graphics.hpp>

class Tutorial {
public:
    Tutorial(sf::RenderWindow& win);
    void Ejecutar(); // Lógica principal del nivel tutorial
private:
    sf::RenderWindow& ventana;
    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;
    sf::Texture personajeTexture;
    sf::Sprite personajeSprite;
    // Aquí se agregarán más elementos (cuerdas, dulces, etc.)
};

#endif // TUTORIAL_HPP
