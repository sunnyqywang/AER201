#include <Servo.h>
#include <Arduino.h>
#include <Keypad.h>
#include "Data.h"
#include "Sensors.h"
#include "GridFollowing.h"
#include "NearHopper.h"
#include "Arm.h"

Servo mySweeper;
Servo myArm;
int index, hopper;
int successApproach = false;
int firstTime = true;
char startKey;

int EnterHopperPosition () {
  
  const byte ROWS = 4; // Four rows
  const byte COLS = 3; // Three columns
  // Define the Keymap
  char keys[ROWS][COLS] = {
      {'1','2','3'},
      {'4','5','6'},
      {'7','8','9'},
      {'#','0','*'}
  };
  // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
  byte rowPins[ROWS] = { 40, 42, 44, 46 };
  // Connect keypad COL0, COL1 and COL2 to these Arduino pins.
  byte colPins[COLS] = { 48, 50, 52 };
  
  // Create the Keypad
  Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

  char key1 = kpd.waitForKey();
  char key2 = kpd.waitForKey();
    
  return ((int) (key1-'0')*10 + (int) (key2-'0')) - 1 ;
  
}


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
    
  LiftArmHalfWay();
  CloseSweeper();
  
  calibrate();

  ForwardMotion();
  
  hopper = EnterHopperPosition();
  
}
  
void loop() {
  
  // 1. Check if it's the first run
  if (!firstTime) {

      LineFollow(2, 2);
      LineFollow(6, 2);
      LineFollow(1, 1);
      LineFollow(1, 2);
      LineFollow(1, 0);
  } else {
      firstTime = false;
  }
  
  // 2. Going to the hopper intersection
  index = 0;
  while (toHopper[hopper][index+1] < 5) {
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
  delay(500);
  
  // 4. Go in hopper
  successApproach = ApproachHopper(toHopper[hopper][index], toHopper[hopper][index+1]);
  
  while (!successApproach) {
      ExitHopper(toHopper[hopper][index], toHopper[hopper][index+1], hopper); 
      delay(500);
      successApproach = ApproachHopper(toHopper[hopper][index], toHopper[hopper][index+1]);
  }
  Serial.println("Inside Hopper, ready to catch");
  delay(500);
  
  // 5. Close Sweeper
  
  CloseSweeper();
  
  Serial.println("Got the ball");
  delay(500);
 
  // 6. Go back to hopper intersection
  //    Reverse the actions when going in the hoppers

  ExitHopper(toHopper[hopper][index], toHopper[hopper][index+1], hopper); 

  Serial.println("Back to hopper intersection");
 
  // 7. Lift arm halfway
  
  LiftArmHalfWay();
  
  Serial.println("Arm lifted, Ready to go");
  delay(300);
 
  // 8. Go to gameboard
  index = 0;
  while (index < 11) {
    
    if (toBoard[hopper][index] == 0 && toBoard[hopper][index+1] != 0)
      Turn(toBoard[hopper][index+1]);
    else if (toBoard[hopper][index] != 0)
      LineFollow(toBoard[hopper][index], toBoard[hopper][index+1]);
      
    index +=2;
  }
  
  StopMotors();
  
  Serial.println("Arrived at the game board, ready to drop");
  delay(500);
  
  // 9. Lift arm all the way to deposit the ball
  
  TurningLeft();
  StartMotors();
  delay(100);
  StopMotors();

  OpenSweeper();
  delay(200);
  ArmAllTheWay();
  delay(2500);
  
  DropArmHalfWay();
  TurningRight();
  StartMotors();
  delay(100);
  StopMotors();
  delay(500);
  
  Serial.println("Done! Did the ball go in? Am I good? Go ahead and compliment me!");
  delay(500);
  
}

