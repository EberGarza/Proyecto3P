#include "Music.hpp"

Music::Music() {}

Music::~Music() {
    stop();
}

bool Music::load(const std::string& filename) {
    loaded = music.openFromFile(filename);
    return loaded;
}

void Music::play() {
    if (loaded) music.play();
}

void Music::pause() {
    if (loaded) music.pause();
}

void Music::stop() {
    if (loaded) music.stop();
}

bool Music::isPlaying() const {
    return loaded && music.getStatus() == sf::Music::Playing;
}
