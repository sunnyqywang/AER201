#include "Sensors.h"
#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  calibrate();
}

void loop() {
  int photo = CheckSensors(0);
  int ir  = CheckSensors(1);
  int turn = CheckSensors(2);
//  Serial.print("Photo:");
//  switch (photo) {
//    case -1:
//      Serial.println("left touch");
//      break;
//    case 1:
//      Serial.println("right touch");
//      break;
//    case 2: 
//      Serial.println("intersection");
//      break;
//    default:
//      Serial.println("go");
//      break;
//  }
  Serial.print("IR:");
  switch (ir) {
    case -1:
      Serial.println("left touch");
      break;
    case 1:
      Serial.println("right touch");
      break;
    case 2: 
      Serial.println("intersection");
      break;
    default:
      Serial.println("go");
      break;
  }
//  Serial.print("Turn:");
//  switch (turn) {
//    case -1:
//      Serial.println("left touch");
//      break;
//    case 1:
//      Serial.println("right touch");
//      break;
//    case 2: 
//      Serial.println("intersection");
//      break;
//    default:
//      Serial.println("go");
//      break;
//  }
  
}

