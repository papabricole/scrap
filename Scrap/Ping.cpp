#include "Ping.h"
#include "Arduino.h"

namespace scrap {

inline void split(unsigned int* a, int n, float x, int& i, int& j)
{
    do {
        while (a[i] < x)
            i++;
        while (x < a[j])
            j--;
        if (i <= j) {
            const unsigned int t = a[i];
            a[i] = a[j];
            a[j] = t;
            i++;
            j--;
        }
    } while (i <= j);
}

unsigned int median(unsigned int* a, int n)
{
    int L = 0;
    int R = n - 1;
    int k = n / 2;
    int i;
    int j;
    while (L < R) {
        unsigned int x = a[k];
        i = L;
        j = R;
        split(a, n, x, i, j);
        if (j < k)
            L = i;
        if (k < i)
            R = j;
    }
    return a[k];
}

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

unsigned int Ping::medianDistance(int maxDistance)
{
    const int numPing = 7;
    unsigned int measures[numPing];
    for (int i = 0; i < numPing; ++i) {
        measures[i] = distance(maxDistance);
    }
    return median(measures, numPing);
}

} // namespace scrap
