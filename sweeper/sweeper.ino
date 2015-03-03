#include <Servo.h>

const int leftMotorCtrlPin1 = 5;
const int leftMotorCtrlPin2 = 4;
const int leftMotorEnablePin = 3;

const int rightMotorCtrlPin1 = 7;
const int rightMotorCtrlPin2 = 8;
const int rightMotorEnablePin = 6;

Servo mySweeper;  

void setup() {
  pinMode(leftMotorCtrlPin1, OUTPUT);
  pinMode(leftMotorCtrlPin2, OUTPUT);
  pinMode(leftMotorEnablePin, OUTPUT);
  
  pinMode(rightMotorCtrlPin1, OUTPUT);
  pinMode(rightMotorCtrlPin2, OUTPUT);
  pinMode(rightMotorEnablePin, OUTPUT);
  
  mySweeper.attach(8); 
  
  digitalWrite(leftMotorCtrlPin1, HIGH);
  digitalWrite(leftMotorCtrlPin2, LOW);
  digitalWrite(rightMotorCtrlPin1, HIGH);
  digitalWrite(rightMotorCtrlPin2, LOW);
  
  analogWrite(leftMotorEnablePin, NORMALSPEED);
  analogWrite(rightMotorEnablePin, NORMALSPEED);
  
  delay(2000);
  
  mySweeper.write(110);
  
  digitalWrite(leftMotorCtrlPin1, HIGH);
  digitalWrite(leftMotorCtrlPin2, LOW);
  digitalWrite(rightMotorCtrlPin1, HIGH);
  digitalWrite(rightMotorCtrlPin2, LOW);
  
  delay(2000);
  
}

void loop() {
  
}


