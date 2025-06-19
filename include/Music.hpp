#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SFML/Audio.hpp>
#include <string>

class Music {
public:
    Music();
    ~Music();
    bool load(const std::string& filename);
    void play();
    void pause();
    void stop();
    bool isPlaying() const;
private:
    sf::Music music;
    bool loaded = false;
};

#endif // MUSIC_HPP
