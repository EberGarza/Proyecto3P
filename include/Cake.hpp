// Cake.hpp - Declaración de la clase Cake (dulce)
#ifndef CAKE_HPP
#define CAKE_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class Cake {
public:
    Cake(const sf::Vector2f& pos);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);
    float getRadius() const; // Declaración del método
private:
    std::vector<sf::Texture> animFrames; // Frames de animación (cake, Cake_Anim_1,2,3, Cake_Re_Anim_2,1)
    int animFrame = 0;
    float animTimer = 0.f;
    float animSpeed = 0.25f; // Tiempo entre frames de brillo
    float animInterval = 1.5f; // Intervalo entre animaciones de brillo
    float animElapsed = 0.f;
    bool animando = false;
    sf::Sprite sprite;
    sf::Vector2f position;
    float radius = 24.f; // radio del dulce
    void iniciarAnimacion();
};

#endif // CAKE_HPP
