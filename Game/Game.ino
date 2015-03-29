// Notes:
// check delay values for angles other than 90 degrees

// manual path finding for toBoard

#include <Servo.h>
#include <Arduino.h>
#include <Keypad.h>
#include "Data.h"
#include "Sensors.h"
#include "GridFollowing.h"
#include "NearHopper.h"
#include "EnterHopperPos.h"
#include "Arm.h"
#include "Ultrasonic.h"

Servo mySweeper;
Servo myArm;
int index, hopper;
int firstTime = true;

void setup() {
  
  Serial.begin(9600);

  mySweeper.attach(9);
  myArm.attach(8);
  
  pinMode(hopperLockPin, INPUT);
  
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
  
  //GetHopperPos();

  ForwardMotion();
  
  
}
  
void loop() {

  // 0. Check if it's the first run
//  if (!firstTime) {
//      LineFollow(BOARDTOSTART[0], BOARDTOSTART[1]);
//      LineFollow(BOARDTOSTART[2], BOARDTOSTART[3]);
//      LineFollow(BOARDTOSTART[4], BOARDTOSTART[5]);
//      LineFollow(BOARDTOSTART[6], BOARDTOSTART[7]);
//      LineFollow(BOARDTOSTART[8], BOARDTOSTART[9]);
//      firstTime = false;
//  }
  
  // 1. Set hopper number, initialize arm and sweeper
  hopper = 1;
  
  LiftArmHalfWay();
  CloseSweeper();
  
  // 2. Going to the hopper intersection
  index = 0;
  while (toHopper[hopper][index+1] < 10) {
    if (toHopper[hopper][index] != 0) {
      LineFollow(toHopper[hopper][index],toHopper[hopper][index+1]);
    } else
      Turn(toHopper[hopper][index+1]);
    index += 2;
  }
  
  Serial.println("Arrived at hopper intersection");
  StopMotors();
  
  // 3. Drop the arm and open the sweeper
  
  ArmDrop();  
  OpenSweeper();
  
  Serial.println("Arm and Sweeper ready");
  delay(1000);
  
  // 4. Go in hopper
  ApproachHopper(toHopper[hopper][index], toHopper[hopper][index+1]);
  //ApproachHopper(2,15);
  Serial.println("Inside Hopper, ready to catch");
  delay(1000);
  
  // 5. Close Sweeper
  
  CloseSweeper();
  
  Serial.print("Got the ball");
  delay(1000);
 
  // 6. Go back to hopper intersection
  //    Reverse the actions when going in the hoppers
  
  ExitHopper(toHopper[hopper][index], toHopper[hopper][index+1]); 

  Serial.println("Back to hopper intersection");
  delay(1000);
 
  // 7. Lift arm halfway
  
  LiftArmHalfWay();
  
  Serial.println("Arm lifted, Ready to go");
  delay(5000);
 
  // 8. Go to gameboard
  index = 0;
  while (index < 7) {
    LineFollow(toBoard[hopper][index], toBoard[hopper][index+1]);
    index +=2;
  }
//  LineFollow(1,1);
//  StopMotors();
//  delay(500);
//  LineFollow(1,2);
//  StopMotors();
//  delay(500);
//  LineFollow(1,2);
//  StopMotors();
//  delay(500);
//  LineFollow(1,2);
//  StopMotors();
//  delay(500);
//  LineFollow(2,0);
  
  StopMotors();
  
  Serial.println("Arrived at the game board, ready to drop");
  delay(1000);
  
  // 9. Lift arm all the way to deposit the ball
  
  ArmAllTheWay();
  delay(1000);
  DropArmHalfWay();
  
  Serial.println("Done! Did the ball go in? Am I good? Go ahead and compliment me!");
  delay(200000000);
  
}

