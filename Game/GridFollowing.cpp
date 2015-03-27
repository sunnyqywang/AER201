//
//  GridFollowing.cpp
//  
//
//  Created by Qingyi Wang on 2015-03-04.
//
//

#include <Arduino.h>
#include "GridFollowing.h"
#include "Sensors.h"
#include "Data.h"

void ForwardMotion() {

  digitalWrite(leftMotorCtrlPin1, HIGH);
  digitalWrite(leftMotorCtrlPin2, LOW);
  digitalWrite(rightMotorCtrlPin1, HIGH);
  digitalWrite(rightMotorCtrlPin2, LOW);
  
}

void BackwardMotion() {

  digitalWrite(leftMotorCtrlPin1, LOW);
  digitalWrite(leftMotorCtrlPin2, HIGH);
  digitalWrite(rightMotorCtrlPin1, LOW);
  digitalWrite(rightMotorCtrlPin2, HIGH);
//  analogWrite(leftMotorEnablePin, LEFTNORMALSPEED);
//  analogWrite(rightMotorEnablePin, RIGHTNORMALSPEED);
  
}

void StopMotors() {
  
  analogWrite(leftMotorEnablePin, 0);
  analogWrite(rightMotorEnablePin, 0);
  
}

void StartMotors() {
  
  analogWrite(leftMotorEnablePin, LEFTNORMALSPEED);
  analogWrite(rightMotorEnablePin, RIGHTNORMALSPEED-43);
  
}

void TurningLeft() {
  
  // Reverse the direction of the left motor
  digitalWrite(rightMotorCtrlPin1, HIGH);
  digitalWrite(rightMotorCtrlPin2, LOW);
  digitalWrite(leftMotorCtrlPin1, LOW);
  digitalWrite(leftMotorCtrlPin2, HIGH);
  
}

void TurningRight() {
  
  // Reverse the direction of the right motor
  digitalWrite(rightMotorCtrlPin1, LOW);
  digitalWrite(rightMotorCtrlPin2, HIGH);
  digitalWrite(leftMotorCtrlPin1, HIGH);
  digitalWrite(leftMotorCtrlPin2, LOW);

}

void Turn(int dir) {
    // 1 for turning left, 2 for turning right
    
    int state = 10;
    int leftdone = 0;
    int rightdone = 0;
    
    StopMotors();
    
    switch (dir) {           
        case 1:          
            // Reverse the direction of the left motor
            TurningLeft();
            break;
        case 2:
            // Reverse the direction of the right motor
            TurningRight();            
            break;
        default: 
            return;
            break;
            
    }
    
    StartMotors();
    
    // Approximate turning time needed
    delay(1000);
    
    // Feedback to check if turning is finished
    
    while (true) {
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
    }
            
    return;
}

void LineFollow(int dist, int dir) {
    
    //Serial.println(dist, dir);
    //delay(3000);
    int drivingInst, photoInst;
    int count = 0;
    int inttime = millis();
    
    ForwardMotion();
    StartMotors();
    
    while (true) {
        
        drivingInst = CheckSensors(1);
        photoInst = CheckSensors(0);
        
        if ((drivingInst != photoInst) && (drivingInst != 0) && (photoInst != 0)) {
            Serial.println("wrong");
            Serial.println(drivingInst);
            Serial.println(photoInst);
            continue;
        }
        
        if ((drivingInst == 0) && (photoInst == 0)) {
          
            Serial.println("Moving forward");
            
            analogWrite(leftMotorEnablePin, LEFTNORMALSPEED);
            analogWrite(rightMotorEnablePin, RIGHTNORMALSPEED);
            
        } else if (drivingInst == 0) {
          
            drivingInst = photoInst;
        }
        
        if (drivingInst == -1) {
            // left sensor touches the line, adjust to the left
            Serial.println("going left");
            analogWrite(leftMotorEnablePin, LEFTSLOWSPEED);
            analogWrite(rightMotorEnablePin, RIGHTFASTSPEED);
            
        }
        
        if (drivingInst == 1) {
            // right sensor touches the line, adjust to the right
            Serial.println("going right");
            analogWrite(leftMotorEnablePin, LEFTFASTSPEED);
            analogWrite(rightMotorEnablePin, RIGHTSLOWSPEED);
            
        }
        
        if (drivingInst == 2) {
            Serial.println("intersection");
            if ((millis() - inttime) > 1500) {
                count++;
                inttime = millis();
                Serial.println("Intersection");
                Serial.println(count);
            }
            
            if (count == dist) {
                //Serial.print("Distance reached");
                // make a turn
                Turn(dir);
                // restore forward motion before returning
                ForwardMotion();
                return;
            }
        }
        
    }
}

