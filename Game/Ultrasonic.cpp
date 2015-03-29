//
//  Ultrasonic.cpp
//  
//
//  Created by Qingyi Wang on 2015-03-27.
//
//

#include "Ultrasonic.h"

void CheckPulse(int expectedDuration) {
    int duration = 2000;
    
    while (duration > expectedDuration){
        
        pinMode(UltrasonicPin, OUTPUT);
        digitalWrite(UltrasonicPin,LOW);
        delay(2);
        digitalWrite(UltrasonicPin,HIGH);
        delay(5);
        digitalWrite(UltrasonicPin,LOW);
        
        pinMode(UltrasonicPin, INPUT);
        duration = pulseIn(UltrasonicPin);
        
        delay(5);
        
    }
    
}