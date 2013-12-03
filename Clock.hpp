#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <SFML/System/Clock.hpp>
#include <iostream>
#include <SFML/Network.hpp>

class Clock {
public:
    enum Mode {
        Local,
        Network
    };

    struct TimeStruct {
        float time;
        float deltaTime;

        TimeStruct(float t, float d) : time(t), deltaTime(d) {}
    };

    Clock(Mode m, sf::TcpSocket* socket);

    TimeStruct tick();

private:
    float lastTick;

    sf::Clock sfClock;

    Mode mode;

    sf::TcpSocket* socket;
};

#endif // CLOCK_HPP
