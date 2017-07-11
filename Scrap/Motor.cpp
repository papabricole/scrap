#include "Motor.h"
#include "Arduino.h"

namespace scrap {

#define MOTOR_TRIM -5
#define PWM_A_SLOW 100 // arbitrary slow speed PWM duty cycle
#define PWM_A_FAST (PWM_A_SLOW + 50) // arbitrary fast speed PWM duty cycle
#define PWM_B_SLOW (PWM_A_SLOW + MOTOR_TRIM)
#define PWM_B_FAST (PWM_A_FAST + MOTOR_TRIM)
#define DIR_DELAY 1000 // brief delay for abrupt motor changes

Motor::Motor(uint8_t A_IA, uint8_t A_IB, uint8_t B_IA, uint8_t B_IB)
    : MOTOR_A_PWM(A_IA)
    , MOTOR_A_DIR(A_IB)
    , MOTOR_B_PWM(B_IA)
    , MOTOR_B_DIR(B_IB)
{
    pinMode(MOTOR_A_DIR, OUTPUT);
    pinMode(MOTOR_A_PWM, OUTPUT);
    pinMode(MOTOR_B_DIR, OUTPUT);
    pinMode(MOTOR_B_PWM, OUTPUT);
    digitalWrite(MOTOR_A_DIR, LOW);
    digitalWrite(MOTOR_A_PWM, LOW);
    digitalWrite(MOTOR_B_DIR, LOW);
    digitalWrite(MOTOR_B_PWM, LOW);
}

void Motor::forward()
{
    digitalWrite(MOTOR_A_DIR, HIGH); // direction = forward
    analogWrite(MOTOR_A_PWM, 255 - PWM_A_SLOW); // PWM speed = slow
    digitalWrite(MOTOR_B_DIR, HIGH); // direction = forward
    analogWrite(MOTOR_B_PWM, 255 - PWM_B_SLOW); // PWM speed = slow
}

void Motor::stop()
{
    digitalWrite(MOTOR_A_DIR, LOW);
    digitalWrite(MOTOR_A_PWM, LOW);
    digitalWrite(MOTOR_B_DIR, LOW);
    digitalWrite(MOTOR_B_PWM, LOW);
}

void Motor::backward()
{
    digitalWrite(MOTOR_A_DIR, LOW); // direction = reverse
    analogWrite(MOTOR_A_PWM, PWM_A_SLOW); // PWM speed = slow
    digitalWrite(MOTOR_B_DIR, LOW); // direction = reverse
    analogWrite(MOTOR_B_PWM, PWM_B_SLOW); // PWM speed = slow
}

void Motor::turnLeft(int ms)
{
    digitalWrite(MOTOR_B_DIR, LOW); // direction = reverse
    analogWrite(MOTOR_B_PWM, PWM_B_SLOW); // PWM speed = slow
    digitalWrite(MOTOR_A_DIR, HIGH); // direction = forward
    analogWrite(MOTOR_A_PWM, 255 - PWM_A_SLOW); // PWM speed = slow
    delay(ms);
    digitalWrite(MOTOR_B_DIR, HIGH); // direction = forward
    analogWrite(MOTOR_B_PWM, 255 - PWM_B_SLOW); // PWM speed = slow
}

void Motor::turnRight(int ms)
{
    digitalWrite(MOTOR_A_DIR, LOW); // direction = reverse
    analogWrite(MOTOR_A_PWM, PWM_A_SLOW); // PWM speed = slow
    digitalWrite(MOTOR_B_DIR, HIGH); // direction = forward
    analogWrite(MOTOR_B_PWM, 255 - PWM_B_SLOW); // PWM speed = slow
    delay(ms);
    digitalWrite(MOTOR_A_DIR, HIGH); // direction = forward
    analogWrite(MOTOR_A_PWM, 255 - PWM_A_SLOW); // PWM speed = slow
}

} // namespace scrap
