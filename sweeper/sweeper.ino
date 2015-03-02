// include the servo library
#include <Servo.h>

Servo myServo;  // create a servo object 

void setup() {
  myServo.attach(3); // attaches the servo on pin 9 to the servo object 
}

void loop() {

  // scale the numbers from the pot 
  //angle = map(potVal, 0, 1023, 0, 179);

  // set the servo position  
  myServo.write(0);

  // wait for the servo to get there 
  delay(1000);
  myServo.write(110);
  delay(1000);
}


