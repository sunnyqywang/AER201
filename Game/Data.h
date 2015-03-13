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

const int leftSensorPin = A3;
const int rightSensorPin = A4;
const int leftPhotoSensorPin = A5;
const int rightPhotoSensorPin = A6;

const int leftLED = 10;
const int rightLED = 11;
const int turnLED = 9;

const int SLOWSPEED = 150;
const int FASTSPEED = 255;
const int NORMALSPEED = 200;

//const int *path[24];
//malloc(sizeof(int) * ) = path[0];
//malloc(sizeof(int) * ) = path[1];
//path[0] = {1,2,3,4,5};



#endif /* defined(____Data__) */
