#include <Servo.h>
#include <Arduino.h>
#include "Data.h"
#include "Sensors.h"
#include "GridFollowing.h"

Servo mySweeper;

void setup() {
  Serial.begin(9600);
  
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  
  mySweeper.attach(12);
  
  pinMode(leftMotorCtrlPin1, OUTPUT);
  pinMode(leftMotorCtrlPin2, OUTPUT);
  pinMode(leftMotorEnablePin, OUTPUT);
 
  pinMode(rightMotorCtrlPin1, OUTPUT);
  pinMode(rightMotorCtrlPin2, OUTPUT);
  pinMode(rightMotorEnablePin, OUTPUT);
  
  pinMode(leftSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);
  pinMode(leftPhotoSensorPin, INPUT);
  pinMode(rightPhotoSensorPin, INPUT);
  
  calibrate();
  
  // Set motors in motion
  digitalWrite(leftMotorCtrlPin1, HIGH);
  digitalWrite(leftMotorCtrlPin2, LOW);
  digitalWrite(rightMotorCtrlPin1, HIGH);
  digitalWrite(rightMotorCtrlPin2, LOW);
  analogWrite(leftMotorEnablePin, NORMALSPEED);
  analogWrite(rightMotorEnablePin, NORMALSPEED);

}
  
void loop() {
//  Turn(1);
//  delay(1000);
//  Serial.println("1");
//  
//  LineFollow(2,2);
//  delay(1000);
//  Serial.println("2");
//  
//  LineFollow(2,1);
//  delay(1000);
//  Serial.println("3");
//  
//  LineFollow(1,2);
//  delay(1000);
//  Serial.println("4");
//  
//  LineFollow(1,0);
LineFollow(3,1);
  
  delay(5000);
  
}

