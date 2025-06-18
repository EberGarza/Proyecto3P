// Tutorial.cpp - Implementación del primer nivel (Tutorial)
#include "Tutorial.hpp"
#include "Controles.hpp"
#include "Cake.hpp"
#include "AlertaAnim.hpp"
#include "Plataforma.hpp"
#include <iostream>
#include <cmath> // Agregado para usar std::sqrt

Tutorial::Tutorial(sf::RenderWindow& win) : ventana(win) {
    // Cargar fondo del nivel
    if (!fondoTexture.loadFromFile("assets/images/Tutorial.png")) {
        std::cerr << "No se pudo cargar el fondo del tutorial.\n";
    }
    fondoSprite.setTexture(fondoTexture);
    // Escalar fondo para cubrir la ventana
    sf::Vector2u winSize = ventana.getSize();
    sf::Vector2u texSize = fondoTexture.getSize();
    float scaleX = static_cast<float>(winSize.x) / texSize.x;
    float scaleY = static_cast<float>(winSize.y) / texSize.y;
    fondoSprite.setScale(scaleX, scaleY);
    // Cargar frames de animación del personaje
    personajeFrames.clear();
    for (int i = 2; i <= 9; ++i) {
        sf::Texture frame;
        std::string nombre = "assets/images/char_1 (" + std::to_string(i) + ").png";
        if (frame.loadFromFile(nombre)) {
            personajeFrames.push_back(frame);
        }
    }
    if (personajeFrames.empty()) {
        sf::Texture frame;
        if (frame.loadFromFile("assets/images/char_1.png")) {
            personajeFrames.push_back(frame);
        }
    }
    personajeSprite.setTexture(personajeFrames[0]);
    // Escalar personaje relativo al alto de la ventana (más grande)
    float personajeScale = (winSize.y * 0.18f) / personajeFrames[0].getSize().y;
    personajeSprite.setScale(personajeScale, personajeScale);
    personajeSprite.setPosition(winSize.x / 2.f - personajeSprite.getGlobalBounds().width / 2.f, winSize.y - personajeSprite.getGlobalBounds().height - 40);
    // Cargar tornillo y posicionar en el centro superior
    if (!tornilloTexture.loadFromFile("assets/images/Tornillo.png")) {
        std::cerr << "No se pudo cargar el tornillo.\n";
    }
    tornilloSprite.setTexture(tornilloTexture);
    float tornilloScale = (winSize.x * 0.06f) / tornilloTexture.getSize().x;
    tornilloSprite.setScale(tornilloScale, tornilloScale);
    tornilloSprite.setOrigin(tornilloTexture.getSize().x/2.f, tornilloTexture.getSize().y/2.f);
    // Margen superior de 2 cm (≈ 75.6 px a 96 ppi)
    float margenSuperior = 2.f * 37.8f; // 75.6 px
    tornilloSprite.setPosition(winSize.x/2.f, margenSuperior + tornilloTexture.getSize().y * tornilloScale / 2.f);
    // Crear cuerda colgando desde el tornillo al centro de la pantalla
    // Longitud máxima de la cuerda: 250 píxeles o hasta el borde inferior visible
    float maxLargoCm = 30.f;
    float maxLargoPx = maxLargoCm * 37.8f; // ≈ 1134 px
    float espacioDisponible = winSize.y - (tornilloSprite.getPosition().y + tornilloTexture.getSize().y * tornilloScale / 2.f) - 20.f; // 20 px de margen inferior
    float largoFinal = std::min(250.f, winSize.y - (tornilloSprite.getPosition().y + tornilloTexture.getSize().y * tornilloScale / 2.f) - 20.f);
    sf::Vector2f start = tornilloSprite.getPosition();
    sf::Vector2f end = start + sf::Vector2f(0, largoFinal);
    rope = new Rope(start, end, 18);
    rope->setFixedStart(true);
    rope->setFixedEnd(false);
    // Crear el cake en el extremo inferior de la cuerda
    if (rope) {
        auto& pts = rope->getPoints();
        if (!pts.empty())
            cake = new Cake(pts.back());
    }
    // Inicializar animación de alerta
    // alerta = AlertaAnim(); // ¡NO reasignar! Esto causa problemas de textura en SFML
    // Crear plataforma centrada en la parte inferior con ancho fijo (200px)
    float plataformaAnchoFijo = 200.f;
    float plataformaScale = plataformaAnchoFijo / 300.f; // Suponiendo que Platform.png tiene 300px de ancho
    sf::Vector2f plataformaPos(winSize.x/2.f, winSize.y - 60.f); // 60px arriba del borde inferior
    plataforma = new Plataforma(plataformaPos, plataformaScale);
    // Usar el borde superior de la plataforma para posicionar al personaje
    sf::FloatRect platBounds = plataforma->getBounds();
    float personajeAncho = personajeSprite.getGlobalBounds().width;
    float personajeAlto = personajeSprite.getGlobalBounds().height;
    float margenVisual = 4.f; // margen pequeño para que se vea bien
    personajeSprite.setPosition(
        plataformaPos.x - personajeAncho/2.f,
        platBounds.top - personajeAlto + margenVisual
    );
    std::cout << "Personaje Y final: " << personajeSprite.getPosition().y << "\n";
}

Tutorial::~Tutorial() {
    if (rope) { delete rope; rope = nullptr; }
    if (cake) { delete cake; cake = nullptr; }
    if (plataforma) { delete plataforma; plataforma = nullptr; }
}

void Tutorial::Ejecutar() {
    // Mostrar cuadro de texto de introducción con control total
    sf::Font font;
    font.loadFromFile("assets/fonts/VCR_OSD_MONO_1.001.ttf");
    // Definir área lógica del cuadro (vectorizada, sin formato)
    sf::Vector2f cuadroSize(ventana.getSize().x * 0.7f, ventana.getSize().y * 0.25f);
    sf::RectangleShape cuadro(cuadroSize);
    cuadro.setFillColor(sf::Color(0,0,0,0)); // Sin fondo, solo para layout
    cuadro.setOrigin(cuadroSize.x/2, cuadroSize.y/2);
    cuadro.setPosition(ventana.getSize().x/2, ventana.getSize().y/2);
    // Padding interno para el texto
    float paddingX = cuadroSize.x * 0.10f;
    float paddingY = cuadroSize.y * 0.13f;
    sf::FloatRect textoArea(cuadro.getPosition().x - cuadroSize.x/2 + paddingX,
                            cuadro.getPosition().y - cuadroSize.y/2 + paddingY,
                            cuadroSize.x - 2*paddingX,
                            cuadroSize.y - 2*paddingY);
    sf::Text texto;
    texto.setFont(font);
    texto.setString("¡Bienvenido al tutorial!\n\nCorta las cuerdas para que el dulce llegue al personaje.\nUsa el mouse para interactuar.\nPresiona cualquier tecla para continuar...");
    // Ajustar tamaño de fuente para que quepa en el área
    unsigned int charSize = static_cast<unsigned int>(textoArea.height / 4.5f);
    texto.setCharacterSize(charSize);
    texto.setFillColor(sf::Color(255,255,255));
    texto.setStyle(sf::Text::Bold);
    // Centrar el texto en el área útil
    sf::FloatRect textBounds = texto.getLocalBounds();
    texto.setOrigin(textBounds.left + textBounds.width/2, textBounds.top + textBounds.height/2);
    texto.setPosition(textoArea.left + textoArea.width/2, textoArea.top + textoArea.height/2);
    bool mostrarIntro = true;
    while (ventana.isOpen() && mostrarIntro) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                ventana.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
                mostrarIntro = false;
            }
        }
        ventana.clear(sf::Color(100, 180, 255));
        ventana.draw(fondoSprite);
        ventana.draw(texto);        // Texto siempre dentro del área lógica
        ventana.display();
    }
    // Bucle principal del tutorial
    bool enNivel = true;
    sf::Clock clock;
    bool cuerdaCortada = false;
    float animFade = 0.f;
    float animFadeSpeed = 1.5f; // segundos para desvanecer
    float cakeVelY = 0.f;
    sf::Texture personajeAlertaTexture;
    bool personajeEnAlerta = false;
    bool alertaMostrada = false;
    while (ventana.isOpen() && enNivel) {
        float dt = clock.restart().asSeconds();
        // Animación del personaje
        personajeAnimTimer += dt;
        if (personajeAnimTimer >= personajeAnimSpeed && personajeFrames.size() > 1) {
            personajeAnimTimer = 0.f;
            personajeFrameActual = (personajeFrameActual + 1) % personajeFrames.size();
            personajeSprite.setTexture(personajeFrames[personajeFrameActual], true);
        }
        sf::Event event;
        while (ventana.pollEvent(event)) {
            Controles::actualizar(event); // Actualizar controles universales
            if (event.type == sf::Event::Closed) {
                ventana.close();
                return;
            }
            if (Controles::teclaPresionada(sf::Keyboard::Escape)) {
                enNivel = false; // Salir del tutorial
            }
            // Implementación de corte de cuerda con el mouse
            if (Controles::mousePresionado(sf::Mouse::Left) && rope && !cuerdaCortada) {
                sf::Vector2f mousePos = ventana.mapPixelToCoords(Controles::mousePos(ventana));
                float minDist = 16.f; // tolerancia en píxeles
                size_t cutIdx = rope->getPoints().size();
                const auto& pts = rope->getPoints();
                for (size_t i = 1; i < pts.size(); ++i) {
                    sf::Vector2f a = pts[i-1];
                    sf::Vector2f b = pts[i];
                    float t = std::max(0.f, std::min(1.f, ((mousePos - a).x * (b - a).x + (mousePos - a).y * (b - a).y) /
                        ((b - a).x * (b - a).x + (b - a).y * (b - a).y)));
                    sf::Vector2f proj = a + t * (b - a);
                    float dist = std::sqrt((mousePos.x - proj.x)*(mousePos.x - proj.x) + (mousePos.y - proj.y)*(mousePos.y - proj.y));
                    if (dist < minDist) {
                        minDist = dist;
                        cutIdx = i;
                    }
                }
                if (cutIdx < rope->getPoints().size()) {
                    rope->cutAtSegment(cutIdx);
                    cuerdaCortada = true;
                    animFade = 0.f;
                }
            }
        }
        // Actualizar física de la cuerda y cake
        if (rope && !cuerdaCortada) {
            rope->update(dt);
            auto& pts = rope->getPoints();
            if (cake && !pts.empty())
                cake->setPosition(pts.back()); // SIEMPRE en el extremo de la cuerda
        }
        if (cake) {
            if (cuerdaCortada) {
                // Animación de caída y desvanecimiento
                cakeVelY += 600.f * dt; // gravedad reducida
                sf::Vector2f pos = cake->getPosition();
                pos.y += cakeVelY * dt;
                cake->setPosition(pos);
                animFade += dt / animFadeSpeed;
                // Mostrar alerta inmediatamente al cortar la cuerda
                if (!alertaMostrada) {
                    // Activar alerta visual sobre el personaje
                    sf::FloatRect pjBounds = personajeSprite.getGlobalBounds();
                    sf::Vector2f pjCenter(pjBounds.left + pjBounds.width/2.f, pjBounds.top + pjBounds.height/2.f);
                    float pjScale = personajeSprite.getScale().x;
                    alerta.activar(pjCenter, pjScale);
                    alertaMostrada = true;
                }
            }
            cake->update(dt);
        }
        // Restaurar animación normal solo cuando cake colisiona con el personaje
        if (alertaMostrada && cake) {
            // Centro del pastel
            sf::Vector2f cakePos = cake->getPosition();
            float cakeRadius = cake->getRadius();
            // Centro del personaje
            sf::FloatRect pjBounds = personajeSprite.getGlobalBounds();
            sf::Vector2f pjCenter(pjBounds.left + pjBounds.width/2.f, pjBounds.top + pjBounds.height/2.f);
            float pjRadius = std::min(pjBounds.width, pjBounds.height) / 2.f * 0.85f; // margen para colisión
            float dist = std::sqrt((cakePos.x - pjCenter.x)*(cakePos.x - pjCenter.x) + (cakePos.y - pjCenter.y)*(cakePos.y - pjCenter.y));
            if (dist <= cakeRadius + pjRadius) {
                personajeSprite.setTexture(personajeFrames[personajeFrameActual], true);
                alertaMostrada = false;
                alerta.forzarDesactivar(); // Ocultar alerta manualmente
            }
        }
        alerta.update(dt);
        ventana.clear(sf::Color(100, 180, 255));
        ventana.draw(fondoSprite);
        ventana.draw(tornilloSprite);
        if (rope) {
            if (!cuerdaCortada) {
                rope->draw(ventana);
            } else {
                // Desvanecer la cuerda sobrante
                sf::RenderStates states;
                states.blendMode = sf::BlendAlpha;
                sf::Color fadeColor(180,120,60, static_cast<sf::Uint8>(255 * (1-animFade)));
                auto& pts = rope->getPoints();
                for (size_t i = 1; i < pts.size(); ++i) {
                    sf::RectangleShape thickLine;
                    sf::Vector2f p0 = pts[i-1];
                    sf::Vector2f p1 = pts[i];
                    sf::Vector2f delta = p1 - p0;
                    float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
                    float angle = std::atan2(delta.y, delta.x) * 180.f / 3.14159265f;
                    thickLine.setSize(sf::Vector2f(length, 8.f));
                    thickLine.setFillColor(fadeColor);
                    thickLine.setOrigin(0, 4.f);
                    thickLine.setPosition(p0);
                    thickLine.setRotation(angle);
                    ventana.draw(thickLine, states);
                }
            }
        }
        if (cake) cake->draw(ventana);
        // Mostrar solo la alerta O el personaje, nunca ambos
        if (alerta.activa()) {
            alerta.draw(ventana);
        } else {
            ventana.draw(personajeSprite);
        }
        if (plataforma) plataforma->draw(ventana);
        ventana.display();
        // Eliminar cuerda visualmente tras la animación
        if (cuerdaCortada && animFade >= 1.f) {
            if (rope) { delete rope; rope = nullptr; }
        }
    }
}
