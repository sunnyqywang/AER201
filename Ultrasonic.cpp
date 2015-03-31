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

void WallFollow(int expectedDuration) {
        
    pinMode(UltrasonictrigPin, OUTPUT);
    digitalWrite(UltrasonictrigPin,LOW);
    delay(2);
    digitalWrite(UltrasonictrigPin,HIGH);
    delay(5);
    digitalWrite(UltrasonictrigPin,LOW);
    
    pinMode(UltrasonicechoPin, INPUT);
    digitalWrite(UltrasonicechoPin, HIGH);
    duration = pulseIn(UltrasonicechoPin,HIGH);
    
    delay(5);
    
}

