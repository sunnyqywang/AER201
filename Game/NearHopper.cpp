//
//  NearHopper.cpp
//  
//
//  Created by Qingyi Wang on 2015-03-20.
//
//

#include "NearHopper.h"
#include "GridFollowing.h"
#include <Arduino.h>
#include "Data.h"

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
    
    analogWrite(leftMotorEnablePin, NORMALSPEED);
    analogWrite(rightMotorEnablePin, NORMALSPEED);
    
    switch (angle) {
        case 10:
            delay(300);
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
    
    ForwardMotion();
    
    time = millis();
    
    analogWrite (leftMotorEnablePin, NORMALSPEED);
    analogWrite (rightMotorEnablePin, NORMALSPEED);
    
    while (leftHopperLock == LOW or rightHopperLock == LOW) {
        
        leftHopperLock = digitalRead(leftHopperLockPin);
        rightHopperLock = digitalRead(rightHopperLockPin);
    
        if (leftHopperLock == HIGH) {
            analogWrite(leftMotorEnablePin, 0);
        }
        if (rightHopperLock == HIGH) {
            analogWrite(rightMotorEnablePin, 0);
        }
    }
    
    timeElapsed = millis()-time;
    
}

void ExitHopper(int dir, int angle) {
    
    BackwardMotion();
    delay(timeElapsed);
    
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
    
    analogWrite(leftMotorEnablePin, NORMALSPEED);
    analogWrite(rightMotorEnablePin, NORMALSPEED);
    
    switch (angle) {
        case 10:
            delay(300);
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
    
}
