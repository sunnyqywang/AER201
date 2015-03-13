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

void calibrate() {
    int time = millis();
    int leftSensor, rightSensor;
    int leftPhotoSensor, rightPhotoSensor;
    
    while ((millis() - time) < 3000) {
        leftSensor = analogRead(leftSensorPin);
        rightSensor = analogRead(rightSensorPin);
        leftPhotoSensor = analogRead(leftPhotoSensorPin);
        rightPhotoSensor = analogRead(rightPhotoSensorPin);

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
    
    // LEDs indicate calibration is done
    digitalWrite(leftLED, HIGH);
    digitalWrite(rightLED, HIGH);
    delay(2000);
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);
    
    return;
}

// get sensor readings and make adjustment decisions
int CheckSensors(bool type) {
    
    // Type: 1 for reading IR; 0 for reading photoresistors
 
    int leftPin, rightPin;
    int leftSensorMapped, rightSensorMapped;
    
    if (type) {
        leftPin = leftSensorPin;
        rightPin = rightSensorPin;
    }else {
        leftPin = leftPhotoSensorPin;
        rightPin = rightPhotoSensorPin;
    }
    
    int leftSensor = analogRead(leftPin);
    int rightSensor = analogRead(rightPin);
    
    if (type) {
        
        leftSensorMapped = map(leftSensor, minLeft, maxLeft, 0, 100);
        rightSensorMapped = map(rightSensor, minRight, maxRight, 0, 100);
        
    } else {
        
        leftSensorMapped = map(leftSensor, minPhotoLeft, maxPhotoLeft, 0, 100);
        rightSensorMapped = map(rightSensor, minPhotoRight, maxPhotoRight, 0, 100);
        
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

