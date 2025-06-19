#ifndef ESTRELLA_HPP
#define ESTRELLA_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Estrella {
public:
    Estrella();
    ~Estrella();
    
    // Inicializar la estrella con una posición específica
    void inicializar(float x, float y, float escala = 1.0f);
    
    // Activar la animación de la estrella (cuando es recogida)
    void recoger();
    
    // Actualizar la animación y estado de la estrella
    void actualizar(float dt);
    
    // Dibujar la estrella en la ventana
    void dibujar(sf::RenderWindow& ventana);
    
    // Comprobar si un punto está dentro de la estrella (colisión)
    bool contienePunto(const sf::Vector2f& punto) const;
    
    // Comprobar si la estrella ha sido recogida
    bool estaRecogida() const;
    
    // Comprobar si la animación de recogida ha terminado
    bool animacionTerminada() const;
    
private:
    sf::Sprite sprite;
    std::vector<sf::Texture> texturas;
    int frameActual;
    float tiempoAcumulado;
    float duracionFrame;
    bool recogida;
    bool animacionFinalizada;
    float tiempoEfecto; // Para efectos visuales adicionales
};

#endif // ESTRELLA_HPP
