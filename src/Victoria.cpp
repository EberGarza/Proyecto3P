#include "Victoria.hpp"

Victoria::Victoria(sf::RenderWindow& window) : window(window), currentTime(0.0f), finished(false) {
    // Cargar una textura simple para la animación
    texture.loadFromFile("assets/images/Final_Anim_1.png");
    sprite.setTexture(texture);
    
    sf::Vector2u texSize = texture.getSize();
    sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
    sprite.setPosition(400, 300);
}

void Victoria::start() {
    currentTime = 0.0f;
    finished = false;
    if (refSprite) setScaleAndPositionFromSprite(*refSprite);
}

void Victoria::update(float deltaTime) {
    if (finished) return;
    
    currentTime += deltaTime;
    if (currentTime >= animationDuration) {
        finished = true;
    }
}

void Victoria::draw() {
    if (!finished) {
        window.draw(sprite);
    }
}

bool Victoria::isFinished() const {
    return finished;
}

void Victoria::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Victoria::setReferenceSprite(const sf::Sprite* refSprite_) {
    refSprite = refSprite_;
}

void Victoria::setScaleAndPositionFromSprite(const sf::Sprite& refSprite) {
    sf::FloatRect refBounds = refSprite.getGlobalBounds();
    sf::Vector2f refCenter(refBounds.left + refBounds.width/2.f, refBounds.top + refBounds.height/2.f);
    sf::Vector2u texSize = sprite.getTexture()->getSize();
    float scaleX = refBounds.width / texSize.x;
    float scaleY = refBounds.height / texSize.y;
    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(refCenter);
}
