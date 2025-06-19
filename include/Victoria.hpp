#ifndef VICTORIA_HPP
#define VICTORIA_HPP

#include <SFML/Graphics.hpp>

class Victoria {
public:
    Victoria(sf::RenderWindow& window);
    void start(); // Inicia la animación
    void update(float deltaTime); // Actualiza la animación
    void draw(); // Dibuja la animación
    bool isFinished() const; // Indica si la animación terminó
    void setPosition(float x, float y); // Establece la posición del sprite
    void setScaleAndPositionFromSprite(const sf::Sprite& refSprite); // Ajustar escala y posición
    void setReferenceSprite(const sf::Sprite* refSprite); // Guardar referencia al sprite del personaje
private:
    sf::RenderWindow& window;
    sf::Sprite sprite;
    sf::Texture texture;
    float animationDuration = 1.5f; // Duración total de la animación en segundos
    float currentTime = 0.0f;
    bool finished;
    const sf::Sprite* refSprite = nullptr; // Referencia al sprite del personaje
};

#endif // VICTORIA_HPP
