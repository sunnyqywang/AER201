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

const int hopperLockPin = A6;

const int LEFTSLOWSPEED = 90;
const int LEFTFASTSPEED = 170;
const int LEFTNORMALSPEED = 200;

const int RIGHTSLOWSPEED = 80;
const int RIGHTFASTSPEED = 160;
const int RIGHTNORMALSPEED = 190;

const int ARMHORIZONTAL = 0;
const int SWEEPERCLOSED = 95;
const int SWEEPEROPEN = 20;

// Stores the path from starting position to the central hoppers
const int toHopper[12][10] = 
          {{2,2,1,1,1,2,2,0,2,30},
           {2,2,2,0,2,15,0,0,0,0},
           {2,2,3,0,2,30,0,0,0,0},
           
           {1,2,2,0,2,5,0,0,0,0},
           {2,2,1,1,1,2,1,0,2,30},
           {1,2,1,0,1,5,0,0,0,0},  
           
           {2,2,2,0,2,30,0,0,0,0},
           {1,2,1,0,2,5,0,0,0,0},          
           {2,2,1,1,1,2,2,30,0,0}, 
           
           {1,2,1,15,0,0,0,0,0,0},
           {2,2,1,0,2,45,0,0,0,0},
           {1,2,2,5,0,0,0,0,0,0}};
          
//Stores the path from the central hoppers to the game board
const int toBoard[12][12] = 
           {{4,2,3,0,0,0,0,0,0,0,0,0},
           {1,1,1,2,4,2,3,0,0,0,0,0},
           {4,2,2,0,0,0,0,0,0,0,0,0},
           {0,1,2,2,5,2,3,0,0,0,0,0},
           {5,2,3,0,0,0,0,0,0,0,0,0},
           {0,1,2,2,6,2,3,0,0,0,0,0},
           {5,2,2,0,0,0,0,0,0,0,0,0},  
           {0,1,2,2,6,2,3,0,0,0,0,0},           
           {6,2,3,0,0,0,0,0,0,0,0,0},           
           {1,1,2,2,6,2,3,0,0,0,0,0},
           {0,1,1,2,6,2,3,0,0,0,0,0},           
           {0,1,1,2,1,1,1,2,6,2,3,0}};
          
          
const int BOARDTOSTART[] = {2,2,6,2,1,1,1,2,1,0}; // dist,dir,dist,dir
           
#endif /* defined(____Data__) */
