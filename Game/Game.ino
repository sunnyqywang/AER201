// Notes:
// need to verify servo attachments
// check delay values for angles other than 90 degrees
// verify microswitch pin assignments
// manual path finding for toBoard

#include <Servo.h>
#include <Arduino.h>
#include <Keypad.h>
#include "Data.h"
#include "Sensors.h"
#include "GridFollowing.h"
#include "NearHopper.h"

Servo mySweeper;
Servo myArm;
int index, hopper;

void setup() {
  
  Serial.begin(9600);
  
  mySweeper.attach(12);
  myArm.attach(13);
  
  pinMode(leftHopperLockPin, INPUT);
  pinMode(rightHopperLockPin, INPUT);
  
  pinMode(leftMotorCtrlPin1, OUTPUT);
  pinMode(leftMotorCtrlPin2, OUTPUT);
  pinMode(leftMotorEnablePin, OUTPUT);
 
  pinMode(rightMotorCtrlPin1, OUTPUT);
  pinMode(rightMotorCtrlPin2, OUTPUT);
  pinMode(rightMotorEnablePin, OUTPUT);
  
  pinMode(leftSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);
  pinMode(leftPhotoSensorPin, INPUT);
  pinMode(rightPhotoSensorPin, INPUT);
  pinMode(leftTurnSensorPin, INPUT);
  pinMode(rightTurnSensorPin, INPUT);
  
  calibrate();
  
  // Set motors in motion
  ForwardMotion();
  analogWrite(leftMotorEnablePin, NORMALSPEED);
  analogWrite(rightMotorEnablePin, NORMALSPEED);
  
}
  
void loop() {
  
  // 1. Set hopper number
  hopper = 2;
  
  // 2. Going to the hopper intersection
  index = 0;
  while (toHopper[hopper][index] < 10) {
    if (toHopper[hopper][index] == 0)
      LineFollow(toHopper[hopper][index],toHopper[hopper][index+1]);
    else
      Turn(toHopper[hopper][index+1]);
    index += 2;
  }
  
  Serial.print("Arrived at hopper intersection");
  delay(2000);
  
  // 3. Drop the arm and open the sweeper
  
  myArm.write(-15);
  delay(200);
  myArm.write(-30);
  delay(200);
  myArm.write(-45);
  
  mySweeper.write(110);
  
  Serial.print("Arm and Sweeper ready");
  delay(2000);
  
  // 4. Go in hopper
  
  ApproachHopper(toHopper[hopper][index], toHopper[hopper][index+1]);
  
  Serial.print("Inside Hopper, ready to catch");
  delay(2000);
  
  // 5. Close Sweeper
  
  mySweeper.write(-110);
  
  Serial.print("Got the ball");
  delay(2000);
  
  // 6. Go back to hopper intersection
  //    Reverse the actions when going in the hoppers
  
  ExitHopper(toHopper[hopper][index], toHopper[hopper][index+1]);
  
  Serial.print("Back to hopper intersection");
  delay(2000);
  
  // 7. Lift arm halfway
  
  myArm.write(-30);
  delay(200);
  myArm.write(-15);
  delay(200);
  myArm.write(0);
  
  Serial.print("Arm lifted, Ready to go");
  delay(2000);
  
  // 8. Go to gameboard
  
  index = 0;
  while (toBoard[hopper][index] !=0) {
    LineFollow(toBoard[hopper][index], toBoard[hopper][index+1]);
    index +=2;
  }
  
  Serial.print("Arrived at the game board, ready to drop");
  delay(2000);
  
  // 9. Lift arm all the way to deposit the ball
  
  myArm.write(15);
  delay(200);
  myArm.write(30);
  delay(200);
  myArm.write(50);
  
  Serial.print("Done! Did the ball go in? Am I good? Go ahead and compliment!");
  delay(2000);
  
}

