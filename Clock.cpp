#include "Clock.hpp"

Clock::Clock(Mode m, sf::TcpSocket* s) {
    this->mode = m;
    this->socket = s;

    switch (mode) {
        case Local:
            sfClock.restart();
            lastTick = sfClock.getElapsedTime().asSeconds();
            break;
        case Network:
            break;
        default:
            break;
    }
}

Clock::TimeStruct Clock::tick() {
    float tick = 0.0f, deltaTime = 0.0f;

    sf::Packet pk;

    switch (mode) {
        case Local:
            std::cout << "hax" << std::flush;
            tick = sfClock.getElapsedTime().asSeconds();
            deltaTime = tick - lastTick;
            lastTick = tick;

            pk << tick;
            socket->send(pk);
            break;
        case Network:
            socket->receive(pk);
            //std::cout << "nhax" << std::flush;

            pk >> tick;
            deltaTime = tick - lastTick;
            lastTick = tick;
            break;
        default:
            break;
    }

    return TimeStruct(tick, deltaTime);
}
float Clock::getElapsedTime(){
     return sfClock.getElapsedTime().asSeconds();
}
