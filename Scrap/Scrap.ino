#include <Servo.h>
#include "Motor.h"
#include "Ping.h"

using namespace scrap;

#define PING_PIN  11  // pin tied to both trigger and echo pins on the ultrasonic sensor.
#define SERVO_PIN 12

#define HG7881_A_IA 3 // !!! PWM PIN !!!
#define HG7881_A_IB 2
#define HG7881_B_IA 6 // !!! PWM PIN !!!
#define HG7881_B_IB 7

#define MAX_DISTANCE 50 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define servoTrim -4
#define servoCenter (90 + servoTrim)
#define servoMin (servoCenter - 30)
#define servoMax (servoCenter + 30)

//#define turntime 350       // Number of milliseconds to turn 90 deg.
#define turntime 175       // Number of milliseconds to turn 45 deg.
#define turnaroundtime 700 // Number of milliseconds to turn 180 deg.
#define distancelimit 30   //If something gets this many cm from the robot it stops and looks for where to go.
                                 
Servo servo;
Ping ping(PING_PIN);
Motor motor(HG7881_A_IA, HG7881_A_IB, HG7881_B_IA, HG7881_B_IB);

char scan()
{
  char choice;
  
  // Ping center
  servo.write(servoCenter);
  delay(300);
  unsigned int centerscanval = ping.distance();
  
  // Ping left
  servo.write(servoMin);
  delay(300);
  unsigned int leftscanval = ping.distance();

  // Ping right
  servo.write(servoMax);
  delay(600);
  unsigned int rightscanval = ping.distance();
  
  // Reset to center
  servo.write(servoCenter);
  
  if (leftscanval > rightscanval && leftscanval > centerscanval) {
    choice = 'l';
  }
  else if (rightscanval > leftscanval && rightscanval > centerscanval) {
    choice = 'r';
  }
  else {
    choice = 's';
  }
  Serial.print("Choice:  ");
  Serial.println(choice);
  return choice;
}

void setup()
{
  Serial.begin(115200);

  servo.attach(SERVO_PIN);
  servo.write(servoCenter);
  delay(100);
}

void loop()
{
  unsigned int distance = ping.distance();
  
  if (distance < distancelimit) {
    motor.stop(); // If something is ahead, stop the motors.
    char turndirection = scan(); //Decide which direction to turn.
    switch (turndirection) {
      case 'r':
        motor.turnLeft(turntime);
        break;
      case 'l':
        motor.turnRight(turntime);
        break;
      case 's':
        motor.turnRight(turnaroundtime);
        break;
    }
  } else {
      motor.forward();
  }
}
