// Rope.cpp - Implementación de la clase Rope (cuerda)
#include "Rope.hpp"
#include <cmath>

Rope::Rope(const sf::Vector2f& start, const sf::Vector2f& end, int segments)
    : color(sf::Color(180, 120, 60)), numSegments(segments), fixedStart(true), fixedEnd(false)
{
    points.clear();
    prevPoints.clear();
    nodes.clear();
    for (int i = 0; i <= segments; ++i) {
        float t = static_cast<float>(i) / segments;
        sf::Vector2f pos = start + t * (end - start);
        points.push_back(pos);
        prevPoints.push_back(pos);
        sf::CircleShape node(4.f);
        node.setFillColor(color);
        node.setOrigin(4.f, 4.f);
        node.setPosition(pos);
        nodes.push_back(node);
    }
    // Calcular y guardar la longitud fija del segmento
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    segmentLength = sqrt(dx * dx + dy * dy) / segments;
    // Cargar textura de la cuerda
    if (!ropeTexture.loadFromFile("assets/images/Rope.png")) {
        // Si falla, se usará solo la línea
    } else {
        ropeSprite.setTexture(ropeTexture);
        ropeSprite.setOrigin(ropeTexture.getSize().x / 2.f, ropeTexture.getSize().y / 2.f);
    }
}

void Rope::update(float dt) {
    // Eliminar oscilación automática: la cuerda solo se moverá si el jugador interactúa
    // Verlet integration
    for (int i = 0; i < points.size(); ++i) {
        if ((i == 0 && fixedStart) || (i == points.size()-1 && fixedEnd)) continue;
        sf::Vector2f temp = points[i];
        points[i] += (points[i] - prevPoints[i]) + gravity * dt * dt;
        prevPoints[i] = temp;
    }
    // Constraints (mantener la distancia entre nodos)
    for (int iter = 0; iter < constraintIterations; ++iter) {
        for (int i = 0; i < points.size() - 1; ++i) {
            sf::Vector2f delta = points[i+1] - points[i];
            float d = sqrt(delta.x * delta.x + delta.y * delta.y);
            float diff = (d - segmentLength) / d;
            if (i != 0 || !fixedStart) {
                points[i] += delta * 0.5f * diff;
            }
            if (i+1 != points.size()-1 || !fixedEnd) {
                points[i+1] -= delta * 0.5f * diff;
            }
        }
    }
    // Actualizar nodos visuales
    for (int i = 0; i < nodes.size(); ++i) {
        nodes[i].setPosition(points[i]);
    }
}

void Rope::draw(sf::RenderWindow& window) {
    // Dibujar la cuerda con líneas gruesas
    for (size_t i = 1; i < points.size(); ++i) {
        sf::RectangleShape thickLine;
        sf::Vector2f p0 = points[i-1];
        sf::Vector2f p1 = points[i];
        sf::Vector2f delta = p1 - p0;
        float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        float angle = std::atan2(delta.y, delta.x) * 180.f / 3.14159265f;
        thickLine.setSize(sf::Vector2f(length, 8.f)); // ancho de la cuerda
        thickLine.setFillColor(color);
        thickLine.setOrigin(0, 4.f);
        thickLine.setPosition(p0);
        thickLine.setRotation(angle);
        window.draw(thickLine);
    }
    // Opcional: dibujar nodos para depuración
    // for (auto& node : nodes) window.draw(node);
}

void Rope::setFixedStart(bool fixed) { fixedStart = fixed; }
void Rope::setFixedEnd(bool fixed) { fixedEnd = fixed; }
std::vector<sf::Vector2f>& Rope::getPoints() { return points; }
void Rope::cutAtSegment(size_t segmentIdx) {
    // Elimina todos los puntos a partir del segmento seleccionado (simula corte)
    if (segmentIdx < points.size() - 1) {
        points.resize(segmentIdx + 1);
        prevPoints.resize(segmentIdx + 1);
        nodes.resize(segmentIdx + 1);
    }
}
