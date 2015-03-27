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

int time;
int timeElapsed;

void ApproachHopper(int dir, int angle) {
    
    int leftHopperLock = LOW;
    int rightHopperLock = LOW;

    
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
    
    switch (angle) {
        case 10:
            delay(300);
            break;
        case 30:
            delay(400);
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
    
    delay(4000);
    
    StopMotors();
//    time = millis();
//    while (leftHopperLock == LOW or rightHopperLock == LOW) {
//        
//        leftHopperLock = digitalRead(leftHopperLockPin);
//        rightHopperLock = digitalRead(rightHopperLockPin);
//    
//        if (leftHopperLock == HIGH) {
//            analogWrite(leftMotorEnablePin, 0);
//        }
//        if (rightHopperLock == HIGH) {
//            analogWrite(rightMotorEnablePin, 0);
//        }
//    }
//    
//    timeElapsed = millis()-time;
    
}

void ExitHopper(int dir, int angle) {
    
    int state = 10;
    int leftdone = 0;
    int rightdone = 0;
    int time = 0;
    int updatedTime = 0;
    int maxTime;
    
    BackwardMotion();
    StartMotors();
    //delay(timeElapsed);
    delay(3000);
    
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
        case 10:
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
