#include "Ping.h"
#include "Arduino.h"

namespace scrap {

Ping::Ping(uint8_t pin)
    : ping_pin(pin)
{
}

unsigned int Ping::distance(int maxDistance)
{
    // Reset the sensor.
    // Some sensors are stuck when there is no echo.
    pinMode(ping_pin, OUTPUT);
    digitalWrite(ping_pin, LOW);
    delayMicroseconds(20);

    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    digitalWrite(ping_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ping_pin, LOW);

    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(ping_pin, INPUT);

    // Sound speed in air is aprox. 343m/s and need 29.1microsecond/cm.
    const unsigned long duration = pulseIn(ping_pin, HIGH, 2 * 29.1f * maxDistance);

    // If we timed out (no echo)
    if (duration == 0)
        return maxDistance;

    return duration * 0.0343f / 2;
}
} // namespace scrap
