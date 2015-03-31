//
//  EnterHopperPos.cpp
//  
//
//  Created by Qingyi Wang on 2015-03-23.
//
//

#include "EnterHopperPos.h"
#include "Arduino.h"

void GetHopperPos(){
  
    char lefthopper1, lefthopper2, righthopper1, righthopper2;
    
    Serial.println("Entry of central hopper positions");
    Serial.print("Enter first digit of left hopper position number: ");
    delay(4000);
    
    if (Serial.available() > 0)
    {
        lefthopper1 = Serial.read();
    }
    Serial.println(lefthopper1);
    
    Serial.print("Enter second digit of left hopper position number: ");
    delay(4000);
    
    if (Serial.available() > 0)
    {
        lefthopper2 = Serial.read();
    }
    
    else
    {
        lefthopper2 = ' ';
    }
    Serial.println(lefthopper2);
    
    
    
    Serial.print("Enter first digit of right hopper position number: ");
    delay(4000);
    if (Serial.available() > 0)
    {
        righthopper1 = Serial.read();
        
    }
    Serial.println(righthopper1);
    
    Serial.print("Enter second digit of right hopper position number: ");
    delay(4000);
    if (Serial.available() > 0)
    {
        righthopper2 = Serial.read();
    }
    
    Serial.println(righthopper2);
    
    
    
    delay(1000);
    Serial.print("The left hopper number is: ");
    Serial.print(lefthopper1);
    Serial.println(lefthopper2);
    Serial.print("The right hopper number is: ");
    Serial.print(righthopper1);
    Serial.println(righthopper2);
    delay(2000);
}
