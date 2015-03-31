//
//  NearHopper.cpp
//  
//
//  Created by Qingyi Wang on 2015-03-20.
//
//

#include <Arduino.h>
#include "NearHopper.h"
#include "GridFollowing.h"
#include "Data.h"
#include "Sensors.h"

unsigned long time;
unsigned long timeElapsed;

extern unsigned long turnTime;

void ApproachHopper(int dir, int angle) {
    
    int HopperLock = 0;
    
    switch (dir) {
        case 1:
            TurningLeft();
            break;
            
        case 2:
            TurningRight();
            break;
            
        default:
            break;
    }
    
    StartMotors();
    
//    switch (angle) {
//        case 15:
//            delay(turnTime/7);
//            break;
//        case 30:
//            delay(turnTime/3);
//            break;
//        case 45:
//            delay(turnTime/2);
//            break;
//        default:
//            break;
//    }
    switch (angle) {
        case 15:
            delay(250);
            break;
        case 30:
            delay(700);
            break;
        case 45:
            delay(800);
            break;
        default:
            break;
    }
    
    StopMotors();
    
    ForwardMotion();
    StartMotors();
    
    time = millis();
    while (HopperLock == 0) {
        
        HopperLock = digitalRead(A6);
        //Serial.println(HopperLock);
        
    }
    StopMotors();
    timeElapsed = millis()-time;
    
}

void ExitHopper(int dir, int angle) {
    
    int state = 10;
    int leftdone = 0;
    int rightdone = 0;
    unsigned long time = 0;
    unsigned long updatedTime = 0;
    unsigned long maxTime;
    int dir1 = dir;
    
    BackwardMotion();
    StartMotors();
    delay(timeElapsed+100);
    StopMotors();
    
    // Reposition LEFT side to align with the line
    switch (angle) {
        case 15:
            maxTime = 350;
            break;
        case 30:
            maxTime = 450;
            break;
        case 45:
            maxTime = 1000;
            break;
        default:
            break;
    }
    
    time = millis();
    updatedTime = millis();
    
    int done = false;
    while (not done) {
        
        switch (dir1) {
            case 1:
                TurningRight();
                break;
                
            case 2:
                TurningLeft();
                break;
                
            default:
                break;
        }
        
        analogWrite(leftMotorEnablePin,LEFTSLOWSPEED);
        
        while (updatedTime - time < maxTime) {
            state = CheckSensors(2);
            
            Serial.println(state);
            
            if (state == -1){
                analogWrite(leftMotorEnablePin, 0);
                done = true;
                break;
            }
            
            updatedTime = millis();
        }
        maxTime += 100;
        if (dir1 == 1) {
            dir1 = 2;
        } else {
            dir1 = 1;
        }

    }
    
    
    // Reposition RIGHT side to align with the line
    switch (angle) {
        case 15:
            maxTime = 350;
            break;
        case 30:
            maxTime = 450;
            break;
        case 45:
            maxTime = 1000;
            break;
        default:
            break;
    }

    time = millis();
    updatedTime = millis();
    
    done = false;
    while (not done) {
        
        switch (dir1) {
            case 1:
                TurningRight();
                break;
                
            case 2:
                TurningLeft();
                break;
                
            default:
                break;
        }
    
        analogWrite(rightMotorEnablePin,RIGHTSLOWSPEED);
        
        while (updatedTime - time < maxTime) {
            state = CheckSensors(2);
            
            Serial.println(state);
            
            if (state == 1){
                analogWrite(rightMotorEnablePin, 0);
                done = true;
                break;
            }
            
            updatedTime = millis();
        }
        maxTime += 100;
        if (dir1 == 1) {
            dir1 = 2;
        } else {
            dir1 = 1;
        }
        
    }
  
}
