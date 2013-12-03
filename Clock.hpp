#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <SFML/System/Clock.hpp>
#include <iostream>

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

    Clock(Mode m);

    TimeStruct tick();

private:
    float lastTick;

    sf::Clock sfClock;

    Mode mode;
};

#endif // CLOCK_HPP
