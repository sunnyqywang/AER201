//
//  Data.h
//  
//
//  Created by Qingyi Wang on 2015-03-04.
//
//

#ifndef ____Data__
#define ____Data__

#include <stdio.h>
#include <Arduino.h>

const int leftMotorCtrlPin1 = 22;
const int leftMotorCtrlPin2 = 23;
const int leftMotorEnablePin = 2;

const int rightMotorCtrlPin1 = 24;
const int rightMotorCtrlPin2 = 25;
const int rightMotorEnablePin = 3;

const int leftSensorPin = A10;
const int rightSensorPin = A13;
const int leftPhotoSensorPin = A11;
const int rightPhotoSensorPin = A14;
const int leftTurnSensorPin = A12;
const int rightTurnSensorPin = A15;

const int leftHopperLockPin = 26;
const int rightHopperLockPin = 27;
const int SLOWSPEED = 180;
const int FASTSPEED = 255;
const int NORMALSPEED = 200;

// Stores the path from starting position to the central hoppers
const int toHopper[12][9] = 
          {{2,2,2,1,1,2,1,2,45},
           {1,2,2,1,10,0,0,0,0},
           {2,2,3,2,30,0,0,0,0},
           {1,2,2,2,30,0,0,0,0},
           {2,2,1,1,1,2,45,0,0},
           {1,2,1,1,10,0,0,0,0},
           {2,2,2,2,45,0,0,0,0},
           {1,2,1,2,10,0,0,0,0},
           {2,2,1,1,1,2,0,2,45},
           {1,2,0,1,10,0,0,0,0},
           {2,2,1,2,45,0,0,0,0},
           {0,1,20,0,0,0,0,0,0}};
          
//Stores the path from the central hoppers to the game board
const int toBoard[12][9] = 
           {{2,2,2,1,1,2,1,2,45},
           {1,2,2,1,10,0,0,0,0},
           {2,2,3,2,30,0,0,0,0},
           {1,2,2,2,30,0,0,0,0},
           {2,2,1,1,1,2,45,0,0},
           {1,2,1,1,10,0,0,0,0},
           {2,2,2,2,45,0,0,0,0},
           {1,2,1,2,10,0,0,0,0},
           {2,2,1,1,1,2,0,2,45},
           {1,2,0,1,10,0,0,0,0},
           {2,2,1,2,45,0,0,0,0},
           {0,1,20,0,0,0,0,0,0}};
#endif /* defined(____Data__) */
