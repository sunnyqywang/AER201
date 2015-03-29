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
#include "Arduino.h"

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

const int leftHopperLockPin = 30;
const int rightHopperLockPin = 31;
const int LEFTSLOWSPEED = 170;
const int LEFTFASTSPEED = 255;
const int LEFTNORMALSPEED = 220;
const int RIGHTSLOWSPEED = 170;
const int RIGHTFASTSPEED = 255;
const int RIGHTNORMALSPEED = 220;

const int ARMHORIZONTAL = 100;
const int SWEEPERCLOSED = 140;
const int SWEEPEROPEN = 70;

// Stores the path from starting position to the central hoppers
const int toHopper[12][9] = 
          {{2,2,2,1,1,2,1,2,45},
           {2,2,2,0,2,30,0,0,0},
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
const int toBoard[12][8] = 
           {{0,4,2,4,0,0,0,0},
           {1,1,1,2,4,2,3,0},
           {1,1,2,4,2,4,0,0},
           {1,2,2,5,2,4,0,0},
           {0,6,2,4,0,0,0,0},
           {1,2,2,6,2,4,0,0},
           {0,0,0,0,0,0,0,0},  //
           {1,2,2,6,2,4,0,0},
           {0,6,2,4,0,0,0,0},
           {0,0,0,0,0,0,0,0},//
           {0,0,0,0,0,0,0,0},//
           {1,2,2,7,2,3,0,0}};
          
          
const int BOARDTOSTART[] = {2,2,6,2,1,1,1,2,2,0}; // dist,dir,dist,dir
           
#endif /* defined(____Data__) */
