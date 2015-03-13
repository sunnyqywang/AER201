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

void Turn(int dir) {
    // 1 for turning left, 2 for turning right
    
    int state0 = -1;
    int state1 = -1;
    int time;
    
    // Stop the motors
    digitalWrite(leftMotorEnablePin, 0);
    digitalWrite(rightMotorEnablePin, 0);
    
    switch (dir) {
            
        case 1:
            
            time = millis();
            
            // Reverse the direction of the left motor
            digitalWrite(rightMotorCtrlPin1, HIGH);
            digitalWrite(rightMotorCtrlPin2, LOW);
            digitalWrite(leftMotorCtrlPin1, LOW);
            digitalWrite(leftMotorCtrlPin2, HIGH);
            
            // Initiate turning motion
            Serial.println("TURNINGGGGG");
            analogWrite(leftMotorEnablePin, 220);
            analogWrite(rightMotorEnablePin, 140);
            
            // Approximate turning time needed
            delay(2200 );
            
            // Feedback to check if turning is finished
            
//            while (true) {
//                state0 = CheckSensors(0);
//                Serial.println(state0);
//                //state1 = CheckSensors(1);
//                if (state0 == -1){
//                  delay(120);
//                  Serial.println("Left done");
//                  analogWrite(leftMotorEnablePin, 0);
//                }
//                if (state0 == 1){
//                  delay(120);
//                  Serial.println("Right done");
//                  analogWrite(rightMotorEnablePin, 0);
//                }
//                if (state0 == 2){
//                    delay(50);
//                    Serial.println("Both done");
//                    break;
//                }
//            }
            break;
        case 2:

            // Reverse the direction of the right motor
            digitalWrite(rightMotorCtrlPin1, LOW);
            digitalWrite(rightMotorCtrlPin2, HIGH);
            digitalWrite(leftMotorCtrlPin1, HIGH);
            digitalWrite(leftMotorCtrlPin2, LOW);
            
            // Initiate turning motion
            analogWrite(leftMotorEnablePin, NORMALSPEED);
            analogWrite(rightMotorEnablePin, NORMALSPEED);
            
            // Approximate turning time needed
            delay(2200);
            
//            while (true) {
//                state0 = CheckSensors(0);
//                state1 = CheckSensors(1);
//                if (state0 == 2 and state1 == 2)
//                    break;
//            }
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
            digitalWrite(leftLED, LOW);
            digitalWrite(rightLED, LOW);
            
            analogWrite(leftMotorEnablePin, NORMALSPEED);
            analogWrite(rightMotorEnablePin, NORMALSPEED);
            
        } else if (drivingInst ==0) {
            drivingInst = photoInst;
        }
        
        if (drivingInst == -1) {
            // left sensor touches the line, adjust to the left
            digitalWrite(leftLED, HIGH);
            digitalWrite(rightLED, LOW);
            Serial.println("going left");
            analogWrite(leftMotorEnablePin, SLOWSPEED);
            analogWrite(rightMotorEnablePin, FASTSPEED);
            
        }
        
        if (drivingInst == 1) {
            // right sensor touches the line, adjust to the right
            digitalWrite(leftLED, LOW);
            digitalWrite(rightLED, HIGH);
            Serial.println("going right");
            analogWrite(leftMotorEnablePin, FASTSPEED);
            analogWrite(rightMotorEnablePin, SLOWSPEED);
            
        }
        
        if (drivingInst == 2) {
            digitalWrite(leftLED, HIGH);
            digitalWrite(rightLED, HIGH);
            Serial.println("intersection");
            delay(100);
            digitalWrite(leftMotorEnablePin, 0);
            digitalWrite(rightMotorEnablePin, 0);
            if ((millis() - inttime) > 1500) {
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
                digitalWrite(leftMotorEnablePin, LOW);
                digitalWrite(rightMotorEnablePin, LOW);
                delay(200);
                digitalWrite(leftMotorCtrlPin1, HIGH);
                digitalWrite(leftMotorCtrlPin2, LOW);
                digitalWrite(rightMotorCtrlPin1, HIGH);
                digitalWrite(rightMotorCtrlPin2, LOW);
                analogWrite(leftMotorEnablePin, NORMALSPEED);
                analogWrite(rightMotorEnablePin, NORMALSPEED);
                delay(500);
                return;
            }
        }
        
    }
}

