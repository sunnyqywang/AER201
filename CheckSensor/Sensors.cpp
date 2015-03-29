//
//  Sensors.cpp
//  
//
//  Created by Qingyi Wang on 2015-03-04.
//
//

#include "Sensors.h"
#include "Data.h"

// Calibrate the sensors
int maxLeft = 0;
int minLeft = 1023;
int maxRight = 0;
int minRight = 1023;
int maxPhotoLeft = 0;
int minPhotoLeft = 1023;
int maxPhotoRight = 0;
int minPhotoRight = 1023;
int maxTurnLeft = 0;
int minTurnLeft = 1023;
int maxTurnRight = 0;
int minTurnRight = 1023;

void calibrate() {
    unsigned long time = millis();
    int leftSensor, rightSensor;
    int leftPhotoSensor, rightPhotoSensor;
    int leftTurnSensor, rightTurnSensor;
    
    digitalWrite(leftMotorCtrlPin1, HIGH);
    digitalWrite(leftMotorCtrlPin2, LOW);
    digitalWrite(rightMotorCtrlPin1, HIGH);
    digitalWrite(rightMotorCtrlPin2, LOW);
    
    while ((millis() - time) < 3000) {
        leftSensor = analogRead(leftSensorPin);
        rightSensor = analogRead(rightSensorPin);
        leftPhotoSensor = analogRead(leftPhotoSensorPin);
        rightPhotoSensor = analogRead(rightPhotoSensorPin);
        leftTurnSensor = analogRead(leftTurnSensorPin);
        rightTurnSensor = analogRead(rightTurnSensorPin);

        if (maxLeft < leftSensor)
            maxLeft = leftSensor;
        if (minLeft > leftSensor)
            minLeft = leftSensor;
        if (maxRight < rightSensor)
            maxRight = rightSensor;
        if (minRight > rightSensor)
            minRight = rightSensor;
        
        if (maxPhotoLeft < leftPhotoSensor)
            maxPhotoLeft = leftPhotoSensor;
        if (minPhotoLeft > leftPhotoSensor)
            minPhotoLeft = leftPhotoSensor;
        if (maxPhotoRight < rightPhotoSensor)
            maxPhotoRight = rightPhotoSensor;
        if (minPhotoRight > rightPhotoSensor)
            minPhotoRight = rightPhotoSensor;

        if (maxTurnLeft < leftTurnSensor)
            maxTurnLeft = leftTurnSensor;
        if (minTurnLeft > leftTurnSensor)
            minTurnLeft = leftTurnSensor;
        if (maxTurnRight < rightTurnSensor)
            maxTurnRight = rightTurnSensor;
        if (minTurnRight > rightTurnSensor)
            minTurnRight = rightTurnSensor;
        
    }
    
    Serial.println("Calibration done\n");
    Serial.print(maxLeft);
    Serial.print("\t");
    Serial.println(minLeft);
    Serial.print(maxRight);
    Serial.print("\t");
    Serial.println(minRight);
    Serial.print(maxPhotoLeft);
    Serial.print("\t");
    Serial.println(minPhotoLeft);
    Serial.print(maxPhotoRight);
    Serial.print("\t");
    Serial.println(minPhotoRight);
    Serial.print(maxTurnLeft);
    Serial.print("\t");
    Serial.println(minTurnLeft);
    Serial.print(maxTurnRight);
    Serial.print("\t");
    Serial.println(minTurnRight);
    
    analogWrite(leftMotorEnablePin, 0);
    analogWrite(rightMotorEnablePin, 0);
    
    delay(3000);
    
    return;
}

// get sensor readings and make adjustment decisions
int CheckSensors(int type) {
    
    // Type: 2 for reading turn sensors; 1 for reading IR; 0 for reading photoresistors
 
    int leftPin, rightPin;
    int leftSensorMapped, rightSensorMapped;
    
    if (type == 2) {
        leftPin = leftTurnSensorPin;
        rightPin = rightTurnSensorPin;
    } else if (type == 1) {
        leftPin = leftSensorPin;
        rightPin = rightSensorPin;
    } else if (type == 0) {
        leftPin = leftPhotoSensorPin;
        rightPin = rightPhotoSensorPin;
    }
    
    int leftSensor = analogRead(leftPin);
    int rightSensor = analogRead(rightPin);
    
    if (type == 0) {
        
        leftSensorMapped = map(leftSensor, minPhotoLeft, maxPhotoLeft, 0, 100);
        rightSensorMapped = map(rightSensor, minPhotoRight, maxPhotoRight, 0, 100);
        
    } else if (type == 1) {
        
        leftSensorMapped = map(leftSensor, minLeft, maxLeft, 0, 100);
        rightSensorMapped = map(rightSensor, minRight, maxRight, 0, 100);
        
    } else if (type == 2) {
      
        leftSensorMapped = map(leftSensor, minTurnLeft, maxTurnLeft, 0, 100);
        rightSensorMapped = map(rightSensor, minTurnRight, maxTurnRight, 0, 100);
    }
    
    if ((leftSensorMapped > 50) and (rightSensorMapped < 50)) 
        // left sensor touches the line while right sensor stays in
        return -1;
        
    if ((rightSensorMapped > 50) and (leftSensorMapped < 50))
        // right sensor touches the line while left sensor stays in
        return 1;
        
    if ((leftSensorMapped > 50) and (rightSensorMapped > 50))
        // both sensors touch the line -> intersection
        return 2;
        
    // no sensor touches line, keep current motion
    return 0;
}

