#include "PantallaVictoria.hpp"
#include "MenuControles.hpp"
#include <iostream>
#include <cmath>  // Añadir para usar sin()

PantallaVictoria::PantallaVictoria(sf::RenderWindow& window) : 
    ventana(window), tiempoEfecto(0.f), velocidadEfecto(2.f), estrellasRecogidas(0), totalEstrellas(3) {
    
    // Cargar fondo - podría ser un nuevo asset o reutilizar uno existente
    if (!fondoTexture.loadFromFile("assets/images/Menu_Principal.png")) {
        std::cerr << "Error al cargar la textura de fondo para la pantalla de victoria\n";
    }
    
    // Configurar el sprite de fondo
    fondoSprite.setTexture(fondoTexture);
    sf::Vector2u winSize = ventana.getSize();
    sf::Vector2u texSize = fondoTexture.getSize();
    float scaleX = static_cast<float>(winSize.x) / texSize.x;
    float scaleY = static_cast<float>(winSize.y) / texSize.y;
    fondoSprite.setScale(scaleX, scaleY);
    
    // Cargar la fuente
    if (!fuente.loadFromFile("assets/fonts/VCR_OSD_MONO_1.001.ttf")) {
        std::cerr << "Error al cargar la fuente para la pantalla de victoria\n";
    }
    
    // Configurar el texto del título
    titulo.setFont(fuente);
    titulo.setString("¡VICTORIA!");
    titulo.setCharacterSize(60);
    titulo.setFillColor(sf::Color(255, 215, 0)); // Color dorado
    sf::FloatRect titleBounds = titulo.getLocalBounds();
    titulo.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    titulo.setPosition(winSize.x / 2.f, winSize.y / 4.f);
    
    // Configurar mensaje de felicitación
    mensaje.setFont(fuente);
    mensaje.setString("¡Has completado el nivel con éxito!");
    mensaje.setCharacterSize(30);
    mensaje.setFillColor(sf::Color::White);
    sf::FloatRect msgBounds = mensaje.getLocalBounds();
    mensaje.setOrigin(msgBounds.width / 2.f, msgBounds.height / 2.f);
    mensaje.setPosition(winSize.x / 2.f, winSize.y / 2.f);
    
    // Configurar instrucción para continuar
    instruccion.setFont(fuente);
    instruccion.setString("Pulsa ENTER para continuar");
    instruccion.setCharacterSize(24);
    instruccion.setFillColor(sf::Color(150, 150, 150));
    sf::FloatRect instBounds = instruccion.getLocalBounds();
    instruccion.setOrigin(instBounds.width / 2.f, instBounds.height / 2.f);
    instruccion.setPosition(winSize.x / 2.f, winSize.y * 3.f / 4.f);
    
    // Configurar texto de estrellas recogidas
    textoEstrellas.setFont(fuente);
    textoEstrellas.setString("Estrellas: 0/3");  // Se actualiza en mostrar()
    textoEstrellas.setCharacterSize(36);
    textoEstrellas.setFillColor(sf::Color(255, 215, 0)); // Color dorado
    sf::FloatRect starBounds = textoEstrellas.getLocalBounds();
    textoEstrellas.setOrigin(starBounds.width / 2.f, starBounds.height / 2.f);
    textoEstrellas.setPosition(winSize.x / 2.f, winSize.y * 0.6f);
}

void PantallaVictoria::mostrar() {
    sf::Clock reloj;
    bool mostrandoPantalla = true;
    
    // Actualizar el texto de estrellas con el valor actual
    textoEstrellas.setString("Estrellas: " + std::to_string(estrellasRecogidas) + "/" + std::to_string(totalEstrellas));
    sf::FloatRect starBounds = textoEstrellas.getLocalBounds();
    textoEstrellas.setOrigin(starBounds.width / 2.f, starBounds.height / 2.f);
    
    while (ventana.isOpen() && mostrandoPantalla) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            MenuControles::actualizar(event);
            
            if (event.type == sf::Event::Closed) {
                ventana.close();
                return;
            }
            
            // Salir al pulsar Intro/Espacio/Escape
            if (MenuControles::Aceptar() || MenuControles::Cancelar()) {
                mostrandoPantalla = false;
            }
        }
        
        // Actualizar efectos
        float deltaTime = reloj.restart().asSeconds();
        tiempoEfecto += deltaTime * velocidadEfecto;
        
        // Efecto de parpadeo para la instrucción
        float alpha = 128 + 127 * sin(tiempoEfecto);
        instruccion.setFillColor(sf::Color(150, 150, 150, static_cast<sf::Uint8>(alpha)));
        
        // Dibujar la escena
        ventana.clear();
        ventana.draw(fondoSprite);
        ventana.draw(titulo);
        ventana.draw(mensaje);
        ventana.draw(textoEstrellas);  // Dibujar contador de estrellas
        ventana.draw(instruccion);
        ventana.display();
    }
}
