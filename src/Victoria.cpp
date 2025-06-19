#include "Victoria.hpp"

Victoria::Victoria(sf::RenderWindow& window) : window(window), animationTime(0.0f), finished(false), finalAnimFrame(0), frameTime(0.0f), finalAnimActive(false) {
    texture.loadFromFile("assets/images/char_1_Win.png");
    sprite.setTexture(texture);
    sf::Vector2u texSize = texture.getSize();
    sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
    sprite.setPosition(400, 300);
    // Cargar secuencia final
    finalTextures.resize(3);
    finalTextures[0].loadFromFile("assets/images/Final_Anim_1.png");
    finalTextures[1].loadFromFile("assets/images/Final_Anim_2.png");
    finalTextures[2].loadFromFile("assets/images/Final_Anim_3.png");
}

void Victoria::start() {
    animationTime = 0.0f;
    finished = false;
    finalAnimActive = false;
    finalAnimFrame = 0;
    frameTime = 0.0f;
    sprite.setTexture(texture);
}

void Victoria::update(float deltaTime) {
    if (finished) return;
    animationTime += deltaTime;
    if (!finalAnimActive && animationTime > 2.0f) {
        finalAnimActive = true;
        animationTime = 0.0f;
        finalAnimFrame = 0;
        frameTime = 0.0f;
        sprite.setTexture(finalTextures[0]);
        if (refSprite) setScaleAndPositionFromSprite(*refSprite);
    }
    if (finalAnimActive && !finished) {
        frameTime += deltaTime;
        if (frameTime >= frameDuration) {
            frameTime = 0.0f;
            finalAnimFrame++;
            if (finalAnimFrame < static_cast<int>(finalTextures.size())) {
                sprite.setTexture(finalTextures[finalAnimFrame]);
                if (refSprite) setScaleAndPositionFromSprite(*refSprite);
            } else {
                finished = true;
                finalAnimActive = false;
            }
        }
    }
}

void Victoria::draw() {
    if (!finished) {
        window.draw(sprite);
        // Dibuja un contorno de color diferente para cada frame final
        if (finalAnimActive) {
            sf::FloatRect bounds = sprite.getGlobalBounds();
            sf::RectangleShape outline(sf::Vector2f(bounds.width, bounds.height));
            outline.setPosition(bounds.left, bounds.top);
            outline.setFillColor(sf::Color::Transparent);
            if (finalAnimFrame == 0) outline.setOutlineColor(sf::Color::Red);
            else if (finalAnimFrame == 1) outline.setOutlineColor(sf::Color::Green);
            else if (finalAnimFrame == 2) outline.setOutlineColor(sf::Color::Blue);
            else outline.setOutlineColor(sf::Color::Yellow);
            outline.setOutlineThickness(4.f);
            window.draw(outline);
        }
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
