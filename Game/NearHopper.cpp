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
            delay(400);
            break;
        case 30:
            delay(600);
            break;
        case 45:
            delay(900);
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
    
    BackwardMotion();
    StartMotors();
    delay(timeElapsed+100);
    
    switch (dir) {
        case 1:
            TurningRight();
            break;
            
        case 2:
            TurningLeft();
            break;
            
        default:
            break;
    }
     
     switch (angle) {
        case 15:
            maxTime = 400;
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
    
    while (updatedTime - time < maxTime) {
        state = CheckSensors(2);
        
        Serial.println(state);
        
        if (state == -1){
          Serial.println("Left done");
          leftdone = 1;
          analogWrite(leftMotorEnablePin, 0);
        }
        
        if (state == 1){
          Serial.println("Right done");
          rightdone = 1;
          analogWrite(rightMotorEnablePin, 0);
        }
        
        if ((state == 2) or (leftdone && rightdone)){
            StopMotors();
            Serial.println("Both done");
            break;
        }
        updatedTime = millis();
    }
    StopMotors();
}
