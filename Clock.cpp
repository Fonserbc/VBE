#include "Clock.hpp"

Clock::Clock(Mode m) {
    this->mode = m;

    switch (mode) {
        case Local:
            sfClock.restart();
            lastTick = sfClock.getElapsedTime().asSeconds();
        case Network:

            break;
        default:
            break;
    }
}

Clock::TimeStruct Clock::tick() {
    float tick, deltaTime;
    switch (mode) {
        case Local:
            tick = sfClock.getElapsedTime().asSeconds();
            deltaTime = tick - lastTick;
            lastTick = tick;
        case Network:

            break;
        default:
            break;
    }

    return TimeStruct(tick, deltaTime);
}
