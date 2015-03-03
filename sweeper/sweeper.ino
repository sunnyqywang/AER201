#include <Servo.h>

Servo mySweeper;  

void setup() {
  mySweeper.attach(8); 
}

void loop() {
  
  // set the servo position  
  mySweeper.write(45);
  // wait for the servo to get there 
  delay(10000);
  
  mySweeper.write(135);
  delay(10000);
  
}


