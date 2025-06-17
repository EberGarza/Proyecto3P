// Tutorial.hpp - Declaración de la clase Tutorial para el primer nivel
#ifndef TUTORIAL_HPP
#define TUTORIAL_HPP
#include <SFML/Graphics.hpp>
#include "Rope.hpp"
#include "Cake.hpp"
#include "AlertaAnim.hpp"
#include <vector>

class Tutorial {
public:
    Tutorial(sf::RenderWindow& win);
    ~Tutorial();
    void Ejecutar(); // Lógica principal del nivel tutorial
private:
    sf::RenderWindow& ventana;
    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;
    // Animación del personaje
    std::vector<sf::Texture> personajeFrames;
    sf::Sprite personajeSprite;
    float personajeAnimTimer = 0.f;
    int personajeFrameActual = 0;
    float personajeAnimSpeed = 0.12f; // segundos por frame
    // Tornillo y cuerda
    sf::Texture tornilloTexture;
    sf::Sprite tornilloSprite;
    Rope* rope = nullptr;
    Cake* cake = nullptr;
    AlertaAnim alerta;
};

#endif // TUTORIAL_HPP
