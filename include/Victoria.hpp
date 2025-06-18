#ifndef VICTORIA_HPP
#define VICTORIA_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Victoria {
public:
    Victoria(sf::RenderWindow& window);
    void start(); // Inicia la animación
    void update(float deltaTime); // Actualiza la animación
    void draw(); // Dibuja la animación
    bool isFinished() const; // Indica si la animación terminó
    void setPosition(float x, float y); // Establece la posición del sprite
    void setScaleAndPositionFromSprite(const sf::Sprite& refSprite); // Declaración del método
    void setReferenceSprite(const sf::Sprite* refSprite); // Nuevo: guardar referencia al sprite del personaje
private:
    sf::RenderWindow& window;
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<sf::Texture> finalTextures;
    int finalAnimFrame = 0;
    float frameTime = 0.0f;
    float frameDuration = 0.3f; // Duración de cada frame
    float animationTime;
    bool finished;
    bool finalAnimActive = false;
    const sf::Sprite* refSprite = nullptr; // Referencia al sprite del personaje
};

#endif // VICTORIA_HPP
