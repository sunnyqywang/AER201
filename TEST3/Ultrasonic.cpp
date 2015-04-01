//
//  Ultrasonic.cpp
//  
//
//  Created by Qingyi Wang on 2015-03-27.
//
//

#include "Ultrasonic.h"
#include <Arduino.h>
#include "Data.h"

int CheckUltrasonic(int expectedDuration) {
        
    pinMode(UltrasonicTrigPin, OUTPUT);
    digitalWrite(UltrasonicTrigPin,LOW);
    delay(2);
    digitalWrite(UltrasonicTrigPin,HIGH);
    delay(5);
    digitalWrite(UltrasonicTrigPin,LOW);
    
    pinMode(UltrasonicEchoPin, INPUT);
    digitalWrite(UltrasonicEchoPin, HIGH);
    int duration = pulseIn(UltrasonicEchoPin,HIGH);
    
    if (duration < expectedDuration - ULTRATHRESHOLD) {
        // Too close to the wall
        return -1;
    } else if (duration < expectedDuration + ULTRATHRESHOLD) {
        // Too far from the wall
        return 1;
    } else
        return 0;
    
}

