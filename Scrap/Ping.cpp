#include "Ping.h"
#include "Arduino.h"

namespace scrap {

Ping::Ping(uint8_t pin)
    : ping_pin(pin)
{
}

unsigned int Ping::distance(int minDistance, int maxDistance)
{
    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(ping_pin, OUTPUT);
    digitalWrite(ping_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(ping_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ping_pin, LOW);

    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(ping_pin, INPUT);
    unsigned long duration = pulseIn(ping_pin, HIGH, 2 * 29 * maxDistance);

    if (duration == 0)
        duration = 2 * 29 * maxDistance;
    if (duration < 2 * 29 * minDistance)
        duration = 2 * 29 * minDistance;

    // convert the time into a distance
    return duration / 29 / 2;
}
} // namespace scrap
