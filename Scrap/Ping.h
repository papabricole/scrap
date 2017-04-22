#pragma once

#include <inttypes.h>

namespace scrap {

class Ping {
public:
    Ping(uint8_t pin);

    unsigned int distance(int minDistance = 10, int maxDistance = 50);

private:
    uint8_t ping_pin;
};

}; // namespace scrap
