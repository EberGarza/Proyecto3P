#include "PantallaVictoria.hpp"
#include "MenuControles.hpp"
#include <iostream>
#include <cmath>     // Para usar sin()
#include <ctime>     // Para time()
#include <cstdlib>   // Para rand() y srand()
#include <algorithm> // Para std::min y std::max

PantallaVictoria::PantallaVictoria(sf::RenderWindow& window) : 
    ventana(window), tiempoEfecto(0.f), velocidadEfecto(2.f) {
    // Inicializar semilla aleatoria para las partículas
    srand(static_cast<unsigned int>(time(nullptr)));
      // Cargar el fondo específico para la pantalla de victoria
    if (!fondoTexture.loadFromFile("assets/images/Victory_Screen.png")) {
        std::cerr << "Error al cargar la textura de fondo Victory_Screen.png para la pantalla de victoria\n";
    }
      // Configurar el sprite de fondo - asegurar que se ajuste perfectamente a la ventana
    fondoSprite.setTexture(fondoTexture);
    sf::Vector2u winSize = ventana.getSize();
    sf::Vector2u texSize = fondoTexture.getSize();
    
    // Calcular la escala preservando proporciones y cubriendo toda la pantalla
    float scaleX = static_cast<float>(winSize.x) / texSize.x;
    float scaleY = static_cast<float>(winSize.y) / texSize.y;
    
    // Usar la escala mayor para cubrir por completo la ventana
    float scale = std::max(scaleX, scaleY);
    fondoSprite.setScale(scale, scale);
    
    // Centrar la imagen
    fondoSprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
    fondoSprite.setPosition(winSize.x / 2.0f, winSize.y / 2.0f);
    
    // Cargar la fuente
    if (!fuente.loadFromFile("assets/fonts/VCR_OSD_MONO_1.001.ttf")) {
        std::cerr << "Error al cargar la fuente para la pantalla de victoria\n";
    }    // Configurar el título principal - simplificado para evitar problemas con caracteres especiales
    titulo.setFont(fuente);
    titulo.setString("NIVEL COMPLETADO");  // Sin caracteres especiales como '¡' o '!'
    titulo.setCharacterSize(40);
    titulo.setFillColor(sf::Color(255, 215, 0)); // Color dorado
    titulo.setOutlineColor(sf::Color(150, 75, 0)); // Contorno marrón para mejor legibilidad
    titulo.setOutlineThickness(1.5f);
    titulo.setStyle(sf::Text::Bold);
    
    // Centrar correctamente el título
    sf::FloatRect titleBounds = titulo.getLocalBounds();
    titulo.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    titulo.setPosition(winSize.x / 2.f, winSize.y * 0.3f); // Posición ajustada para visualización óptima
      // Configurar mensaje de felicitación - más visible y centrado, sin caracteres especiales
    mensaje.setFont(fuente);
    mensaje.setString("Has superado el tutorial con exito!"); // Sin caracteres especiales
    mensaje.setCharacterSize(26);
    mensaje.setFillColor(sf::Color(255, 255, 255)); // Blanco completamente opaco
    mensaje.setOutlineColor(sf::Color(50, 50, 50)); // Contorno gris oscuro completamente opaco
    mensaje.setOutlineThickness(1.0f);
    
    // Centrar correctamente el mensaje
    sf::FloatRect msgBounds = mensaje.getLocalBounds();
    mensaje.setOrigin(msgBounds.width / 2.f, msgBounds.height / 2.f);
    mensaje.setPosition(winSize.x / 2.f, winSize.y * 0.7f); // Ajustado para mejor visibilidad    // Configurar instrucción para continuar - más visible y con mejor contraste
    instruccion.setFont(fuente);
    instruccion.setString("Pulsa ENTER para continuar");
    instruccion.setCharacterSize(22);
    instruccion.setFillColor(sf::Color(220, 220, 220)); // Color más claro para mejor contraste
    instruccion.setOutlineColor(sf::Color(0, 0, 0, 200)); // Borde negro para mayor legibilidad
    instruccion.setOutlineThickness(1.0f);
    instruccion.setStyle(sf::Text::Bold);
    
    // Centrar correctamente la instrucción
    sf::FloatRect instBounds = instruccion.getLocalBounds();
    instruccion.setOrigin(instBounds.width / 2.f, instBounds.height / 2.f);
    instruccion.setPosition(winSize.x / 2.f, winSize.y * 0.85f); // Ajustado para mejor visibilidad
      // Se eliminó la configuración del texto de estrellas
}

void PantallaVictoria::mostrar() {
    sf::Clock reloj;
    bool mostrandoPantalla = true;
    
    // Se eliminó la actualización del texto de estrellas
    
    // Efecto de aparición gradual
    float opacidad = 0.0f;
    float velocidadAparicion = 1.0f; // Velocidad de fade-in
    bool fadeInCompleto = false;
    
    // Efectos de partículas para celebración
    struct Particula {
        sf::CircleShape forma;
        sf::Vector2f velocidad;
        float vida;
    };
    
    std::vector<Particula> particulas;
    float tiempoGeneracion = 0.0f;
    
    while (ventana.isOpen() && mostrandoPantalla) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            MenuControles::actualizar(event);
            
            if (event.type == sf::Event::Closed) {
                ventana.close();
                return;
            }
            
            // Salir al pulsar Intro/Espacio/Escape, pero solo después de fade-in
            if (fadeInCompleto && (MenuControles::Aceptar() || MenuControles::Cancelar())) {
                mostrandoPantalla = false;
            }
        }
          // Actualizar efectos
        float deltaTime = reloj.restart().asSeconds();
        tiempoEfecto += deltaTime * velocidadEfecto;
        
        // Asegurarse de que el título siempre esté en la posición correcta (evitar bugs)
        sf::Vector2u winSize = ventana.getSize();
        titulo.setPosition(winSize.x / 2.f, winSize.y * 0.3f);
        
        // Efecto de aparición gradual (fade-in)
        if (!fadeInCompleto) {
            opacidad += deltaTime * velocidadAparicion;
            if (opacidad >= 1.0f) {
                opacidad = 1.0f;
                fadeInCompleto = true;
            }
            
            // Aplicar opacidad a todos los elementos
            sf::Uint8 alpha = static_cast<sf::Uint8>(255 * opacidad);
            sf::Color color = fondoSprite.getColor();
            color.a = alpha;
            fondoSprite.setColor(color);
            
            color = titulo.getFillColor();
            color.a = alpha;
            titulo.setFillColor(color);
            
            color = mensaje.getFillColor();
            color.a = alpha;
            mensaje.setFillColor(color);
        }        // Efecto de parpadeo simplificado para la instrucción solo cuando fade-in ha terminado
        if (fadeInCompleto) {
            // Parpadeo más simple, solo alternando entre dos estados
            bool visible = (static_cast<int>(tiempoEfecto * 1.5f) % 2) == 0;
            
            if (visible) {
                instruccion.setFillColor(sf::Color(255, 255, 255, 255)); // Completamente visible
                instruccion.setOutlineColor(sf::Color(0, 0, 0, 255));
            } else {
                instruccion.setFillColor(sf::Color(255, 255, 255, 180)); // Semi transparente
                instruccion.setOutlineColor(sf::Color(0, 0, 0, 180));
            }
            
            // Generar partículas de celebración
            tiempoGeneracion += deltaTime;
            if (tiempoGeneracion >= 0.05f) { // Generar cada 50ms
                tiempoGeneracion = 0.0f;
                
                // Crear nueva partícula
                Particula p;
                p.forma.setRadius(1.0f + static_cast<float>(rand() % 3));
                
                // Color aleatorio entre dorado, blanco y azul claro
                int colorType = rand() % 3;
                if (colorType == 0) {
                    p.forma.setFillColor(sf::Color(255, 215, 0)); // Dorado
                } else if (colorType == 1) {
                    p.forma.setFillColor(sf::Color(255, 255, 255)); // Blanco
                } else {
                    p.forma.setFillColor(sf::Color(135, 206, 250)); // Azul claro
                }
                
                // Posición aleatoria en la parte superior de la pantalla
                float x = static_cast<float>(rand() % ventana.getSize().x);
                p.forma.setPosition(x, -10.0f);
                
                // Velocidad aleatoria
                p.velocidad.x = -50.0f + static_cast<float>(rand() % 100);
                p.velocidad.y = 100.0f + static_cast<float>(rand() % 150);
                
                // Vida aleatoria
                p.vida = 2.0f + static_cast<float>(rand() % 3);
                
                // Añadir a la lista
                particulas.push_back(p);
            }
            
            // Actualizar partículas
            for (size_t i = 0; i < particulas.size(); i++) {
                Particula& p = particulas[i];
                p.forma.move(p.velocidad * deltaTime);
                p.vida -= deltaTime;
                
                // Hacer que la partícula se desvanezca al final de su vida
                if (p.vida < 1.0f) {
                    sf::Color color = p.forma.getFillColor();
                    color.a = static_cast<sf::Uint8>(255 * p.vida);
                    p.forma.setFillColor(color);
                }
                
                // Eliminar partículas muertas o fuera de la pantalla
                if (p.vida <= 0.0f || p.forma.getPosition().y > ventana.getSize().y) {
                    particulas.erase(particulas.begin() + i);
                    i--;
                }
            }
        }            // Aplicar un efecto sutil al título sin moverlo de posición
            if (fadeInCompleto) {
                // Solo aplicar un cambio sutil de brillo sin mover el texto
                float brilloFactor = 0.95f + 0.05f * sin(tiempoEfecto * 1.5f);
                sf::Color colorTitulo = titulo.getFillColor();
                colorTitulo.r = static_cast<sf::Uint8>(std::min(255, static_cast<int>(255 * brilloFactor)));
                colorTitulo.g = static_cast<sf::Uint8>(std::min(255, static_cast<int>(215 * brilloFactor)));
                titulo.setFillColor(colorTitulo);
                
                // Mantener la posición fija para evitar problemas
                sf::Vector2u winSize = ventana.getSize();
                titulo.setPosition(winSize.x / 2.f, winSize.y * 0.3f);
            }
            
            // Dibujar la escena
            ventana.clear();
            ventana.draw(fondoSprite);
            
            // Dibujar partículas
            for (const auto& p : particulas) {
                ventana.draw(p.forma);
            }
            
            ventana.draw(titulo);
            ventana.draw(mensaje);
            ventana.draw(instruccion);
        ventana.display();
    }
}
