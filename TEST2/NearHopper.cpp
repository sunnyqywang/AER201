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

int ApproachHopper(int dir, int angle) {
    
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
    
    switch (angle) {
        case 15:
            delay(250);
            break;
        case 30:
            delay(700);
            break;
        case 45:
            delay(1000);
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
        if (millis() - time > 2500) 
           break; 
           
    }
    StopMotors();
    
    if (HopperLock == 1) {
      timeElapsed = millis()-time;
      return 1;
    }else {
      timeElapsed = 2000;
      return 0;
    }
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
            maxTime = 800;
            break;
        case 45:
            maxTime = 1000;
            break;
        default:
            break;
    }
    
    int done = false;
    
    while (!done) {
        
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
        
        analogWrite(rightMotorEnablePin, 0);
        analogWrite(leftMotorEnablePin, LEFTNORMALSPEED);
        
        time = millis();
        updatedTime = millis();
        
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
        
        maxTime += 200;
        
        if (dir1 == 1) {
            dir1 = 2;
        } else {
            dir1 = 1;
        }

    }
    Serial.println("Leftdone");
    
    
    // Reposition RIGHT side to align with the line
    switch (angle) {
        case 15:
            maxTime = 350;
            break;
        case 30:
            maxTime = 800;
            break;
        case 45:
            maxTime = 1000;
            break;
        default:
            break;
    }
    
    done = false;
    while (!done) {
        
        switch (dir1) {
            case 1:
                TurningLeft();
                break;
                
            case 2:
                TurningRight();
                break;
                
            default:
                break;
        }
        
        analogWrite(leftMotorEnablePin,0);
        analogWrite(rightMotorEnablePin,RIGHTNORMALSPEED);
        
        time = millis();
        updatedTime = millis();
        
        while (updatedTime - time < maxTime) {
        //while (true) {
            state = CheckSensors(2);
            
            Serial.println(state);
            
            if (state == 1){
                analogWrite(rightMotorEnablePin, 0);
                done = true;
                break;
            }
            
            updatedTime = millis();
        }
        
        maxTime += 200;
        
        if (dir1 == 1) {
            dir1 = 2;
        } else {
            dir1 = 1;
        }
        
    }
    Serial.println("Rightdone");
    StopMotors();
  
}
