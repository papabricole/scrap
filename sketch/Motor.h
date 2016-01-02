#pragma once

#include <inttypes.h>

namespace scrap
{

class Motor
{
  public:
    Motor(uint8_t A_IA, uint8_t A_IB, uint8_t B_IA, uint8_t B_IB);

    void forward();
    void stop();
    void backward();
    void turnLeft(int ms = 400);
    void turnRight(int ms = 400);

  private:
    uint8_t MOTOR_A_PWM; // Motor B PWM Speed
    uint8_t MOTOR_A_DIR; // Motor B Direction
    uint8_t MOTOR_B_PWM; // Motor B PWM Speed
    uint8_t MOTOR_B_DIR; // Motor B Direction
};

}; // namespace Scrap
