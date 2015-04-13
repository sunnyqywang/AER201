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
        case 5:
            delay(100);
            break;
        case 15:
            delay(240);
            break;
        case 30:
            delay(650);
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
        if (millis() - time > 3000) 
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

void ExitHopper(int dir, int angle, int hopper) {
    
    int state = 10;
    int leftdone = 0;
    int rightdone = 0;
    unsigned long time;
    unsigned long maxTime;
    int count = 0;
    int done = 0;
    BackwardMotion();
    StartMotors();
    
    while (!done) {
      state = CheckSensors(2);
      Serial.println(state);
      if (hopper == 5 or hopper == 11 or hopper == 9) {
        if (state == -1 or state == 2){
          count++;
          Serial.println(count);
          delay(150);
        }
      } else if (state == 1 or state == 2){
          count++;
          Serial.println(count);
          delay(150);
      }
      
      if (hopper == 2 or hopper == 4 or hopper == 5 or hopper == 6 or hopper == 8 or hopper == 9 or hopper == 10 or hopper == 11) {
        if (count == 1) 
          done = true;
      }
      if (count == 2)
          done = true;
      
    }
    
//    switch (angle) {
//      case 5:
//        delay(50);
//        break;
//      case 15:
//        delay(250);
//        break;
//      case 30:
//        delay(300);
//        break;
//      case 45:
//        delay(750);
//        break;
//      default:
//        break;
//    }
    switch (angle) {
      case 5:
        //delay(50);
        break;
      case 15:
        delay(100);
        break;
      case 30:
        delay(150);
        break;
      case 45:
        delay(600);
        break;
      default:
        break;
    }
    StopMotors();
        
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
    
    analogWrite(rightMotorEnablePin, 0);
    analogWrite(leftMotorEnablePin, LEFTFASTSPEED);
    
    //while (updatedTime - time < maxTime) {
    while (true) {
        state = CheckSensors(2);
        
        Serial.println(state);
        
        if (state == -1 or state == 2){
            analogWrite(leftMotorEnablePin, 0);
            break;
        }
        
    }

    Serial.println("Leftdone");
        
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
    
    analogWrite(leftMotorEnablePin,0);
    analogWrite(rightMotorEnablePin,RIGHTFASTSPEED);
    
    //while (updatedTime - time < maxTime) {
    while (true) {
        state = CheckSensors(2);
        
        Serial.println(state);
        
        if (state == 1 or state == 2){
            analogWrite(rightMotorEnablePin, 0);
            break;
        }

    }
    
    Serial.println("Rightdone");
    
    if (hopper == 2 or hopper == 1 or hopper == 4) {
      TurningRight();
      analogWrite(rightMotorEnablePin, 0);
      analogWrite(leftMotorEnablePin, LEFTNORMALSPEED);
      delay(300);
      TurningLeft();
      analogWrite(rightMotorEnablePin, RIGHTNORMALSPEED);
      analogWrite(leftMotorEnablePin, 0);
      delay(300);
    }
    
    if (hopper == 100) {
      TurningLeft();
      analogWrite(rightMotorEnablePin, RIGHTNORMALSPEED);
      analogWrite(leftMotorEnablePin, 0);
      delay(1000);
      StopMotors();
      TurningRight();
      analogWrite(rightMotorEnablePin, 0);
      analogWrite(leftMotorEnablePin, LEFTNORMALSPEED);
      delay(1000);
    }
    
    StopMotors();
}

