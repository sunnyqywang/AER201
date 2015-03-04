#include <Servo.h>

const int leftMotorCtrlPin1 = 5;
const int leftMotorCtrlPin2 = 4;
const int leftMotorEnablePin = 3;

const int rightMotorCtrlPin1 = 7;
const int rightMotorCtrlPin2 = 8;
const int rightMotorEnablePin = 6;

const int led1 = 10;
const int led2 = 11;
Servo mySweeper;  

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(leftMotorCtrlPin1, OUTPUT);
  pinMode(leftMotorCtrlPin2, OUTPUT);
  pinMode(leftMotorEnablePin, OUTPUT);
  
  pinMode(rightMotorCtrlPin1, OUTPUT);
  pinMode(rightMotorCtrlPin2, OUTPUT);
  pinMode(rightMotorEnablePin, OUTPUT);
  
  mySweeper.attach(12); 
  
  
  
}

void loop() {
  
  mySweeper.write(-110);
  
  delay(2000);
  
  digitalWrite(leftMotorCtrlPin1, HIGH);
  digitalWrite(leftMotorCtrlPin2, LOW);
  digitalWrite(rightMotorCtrlPin1, HIGH);
  digitalWrite(rightMotorCtrlPin2, LOW);
  
  analogWrite(leftMotorEnablePin, 200);
  analogWrite(rightMotorEnablePin, 200);
  
  delay(2000);
  
  analogWrite(leftMotorEnablePin, 0);
  analogWrite(rightMotorEnablePin, 0);
  
  delay(2000);
  mySweeper.write(110);
  delay(2000);
  
  digitalWrite(led2, 1);
  digitalWrite(leftMotorCtrlPin1, LOW);
  digitalWrite(leftMotorCtrlPin2, HIGH);
  digitalWrite(rightMotorCtrlPin1, LOW);
  digitalWrite(rightMotorCtrlPin2, HIGH);
  analogWrite(leftMotorEnablePin, 200);
  analogWrite(rightMotorEnablePin, 200);
  
  delay(2000);
  
  digitalWrite(leftMotorEnablePin, 0);
  digitalWrite(rightMotorEnablePin, 0);
  
  delay(100000000);
}


