// Tutorial.cpp - Implementación del primer nivel (Tutorial)
#include "Tutorial.hpp"
#include <iostream>

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
    // Cargar personaje principal
    if (!personajeTexture.loadFromFile("assets/images/char_1.png")) {
        std::cerr << "No se pudo cargar el personaje.\n";
    }
    personajeSprite.setTexture(personajeTexture);
    // Escalar personaje relativo al alto de la ventana
    float personajeScale = (winSize.y * 0.18f) / personajeTexture.getSize().y;
    personajeSprite.setScale(personajeScale, personajeScale);
    personajeSprite.setPosition(winSize.x / 2.f - personajeSprite.getGlobalBounds().width / 2.f, winSize.y - personajeSprite.getGlobalBounds().height - 40);
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
    // Superponer el asset
    sf::Texture cuadroTexture;
    cuadroTexture.loadFromFile("assets/images/Text_Box_1.png");
    sf::Sprite cuadroSprite(cuadroTexture);
    float scaleX = cuadroSize.x / cuadroTexture.getSize().x;
    float scaleY = cuadroSize.y / cuadroTexture.getSize().y;
    cuadroSprite.setScale(scaleX, scaleY);
    cuadroSprite.setOrigin(cuadroTexture.getSize().x/2.f, cuadroTexture.getSize().y/2.f);
    cuadroSprite.setPosition(cuadro.getPosition());
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
        ventana.draw(cuadroSprite); // Asset
        ventana.draw(texto);        // Texto siempre dentro del área lógica
        ventana.display();
    }
    // Bucle principal del tutorial
    bool enNivel = true;
    while (ventana.isOpen() && enNivel) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                ventana.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                enNivel = false; // Salir del tutorial
            }
        }
        ventana.clear(sf::Color(100, 180, 255));
        ventana.draw(fondoSprite);
        ventana.draw(personajeSprite);
        // Aquí se dibujarán más elementos (cuerdas, dulces, etc.)
        ventana.display();
    }
}
