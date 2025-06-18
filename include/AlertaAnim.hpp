// AlertaAnim.hpp - Maneja la textura de alerta del personaje
#ifndef ALERTA_ANIM_HPP
#define ALERTA_ANIM_HPP
#include <SFML/Graphics.hpp>

class AlertaAnim {
public:
    AlertaAnim();
    void activar(const sf::Vector2f& pos, float scale);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool activa() const;
    void forzarDesactivar(); // Método para desactivar manualmente la alerta
private:
    sf::Texture textura;
    sf::Sprite sprite;
    bool visible = false;
    float timer = 0.f;
    float duracion = 0.5f; // medio segundo
};

#endif // ALERTA_ANIM_HPP
