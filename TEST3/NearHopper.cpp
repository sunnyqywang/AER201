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
            delay(65);
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
    
    BackwardMotion();
    
    StartMotors();
    
    delay(1800);
    
    StopMotors();
}

