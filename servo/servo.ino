
#include <Servo.h>

Servo myServo;  // create a servo object 

void setup() {
  myServo.attach(8); // attaches the servo on pin 9 to the servo object 
}

void loop() {
  
  myServo.write(60);

}

