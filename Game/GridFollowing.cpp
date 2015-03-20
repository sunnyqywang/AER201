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
  analogWrite(leftMotorEnablePin, NORMALSPEED);
  analogWrite(rightMotorEnablePin, NORMALSPEED);
  
}

void BackwardMotion() {

  digitalWrite(leftMotorCtrlPin1, LOW);
  digitalWrite(leftMotorCtrlPin2, HIGH);
  digitalWrite(rightMotorCtrlPin1, LOW);
  digitalWrite(rightMotorCtrlPin2, HIGH);
  analogWrite(leftMotorEnablePin, NORMALSPEED);
  analogWrite(rightMotorEnablePin, NORMALSPEED);
  
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
    
    // Stop the motors
    digitalWrite(leftMotorEnablePin, 0);
    digitalWrite(rightMotorEnablePin, 0);
    
    switch (dir) {
            
        case 1:
            
            // Reverse the direction of the left motor
            TurningLeft();
            
            // Initiate turning motion
            Serial.println("TURNING");
            analogWrite(leftMotorEnablePin, NORMALSPEED);
            analogWrite(rightMotorEnablePin, NORMALSPEED-40);
            
            // Get off the line
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
                    analogWrite(leftMotorEnablePin, 0);
                    analogWrite(rightMotorEnablePin, 0);
                    Serial.println("Both done");
                    break;
                }
            }
            
            break;
        case 2:

            // Reverse the direction of the right motor
            TurningRight();
            
            // Initiate turning motion
            analogWrite(leftMotorEnablePin, NORMALSPEED);
            analogWrite(rightMotorEnablePin, NORMALSPEED);
            
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
                    analogWrite(leftMotorEnablePin, 0);
                    analogWrite(rightMotorEnablePin, 0);
                    Serial.println("Both done");
                    break;
                }
            }
            
            break;
        default: 
            break;
            
    }
    
    return;
}

void LineFollow(int dist, int dir) {
    
    int drivingInst, photoInst;
    int count = 0;
    int inttime = millis();
    
    while (true) {
        
        drivingInst = CheckSensors(1);
        photoInst = CheckSensors(0);
        
        if ((drivingInst != photoInst) && (drivingInst != 0) && (photoInst != 0)) {
            Serial.println("wrong");
            continue;
        }
        
        if ((drivingInst == 0) && (photoInst == 0)) {
          
            Serial.println("Moving forward");
            
            analogWrite(leftMotorEnablePin, NORMALSPEED);
            analogWrite(rightMotorEnablePin, NORMALSPEED);
            
        } else if (drivingInst == 0) {
          
            drivingInst = photoInst;
        }
        
        if (drivingInst == -1) {
            // left sensor touches the line, adjust to the left
            Serial.println("going left");
            analogWrite(leftMotorEnablePin, SLOWSPEED);
            analogWrite(rightMotorEnablePin, FASTSPEED);
            
        }
        
        if (drivingInst == 1) {
            // right sensor touches the line, adjust to the right
            Serial.println("going right");
            analogWrite(leftMotorEnablePin, FASTSPEED);
            analogWrite(rightMotorEnablePin, SLOWSPEED);
            
        }
        
        if (drivingInst == 2) {
            Serial.println("intersection");
            if ((millis() - inttime) > 1000) {
                count++;
                inttime = millis();
                Serial.println("Intersection");
                Serial.println(count);
            }
            
            if (count == dist) {
                Serial.print("Distance reached");
                // make a turn
                Turn(dir);
                // restore forward motion before returning
                ForwardMotion();
                return;
            }
        }
        
    }
}

