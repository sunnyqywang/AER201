// pin assignments
#include <Servo.h>

Servo mySweeper;

const int leftMotorCtrlPin1 = 5;
const int leftMotorCtrlPin2 = 4;
const int leftMotorEnablePin = 3;

const int rightMotorCtrlPin1 = 7;
const int rightMotorCtrlPin2 = 8;
const int rightMotorEnablePin = 6;

const int leftSensorPin = A4;
const int rightSensorPin = A5;
const int leftPhotoSensorPin = A3;
const int rightPhotoSensorPin = A2;


const int leftLED = 10;
const int rightLED = 11;
const int turnLED = 9;

// initialize global variables
int maxLeft = 0;
int minLeft = 1023;
int maxRight = 0;
int minRight = 1023;
int maxPhotoLeft = 0;
int minPhotoLeft = 1023;
int maxPhotoRight = 0;
int minPhotoRight = 1023;

const int SLOWSPEED = 180;
const int FASTSPEED = 220;
const int NORMALSPEED = 200;

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
  
  pinMode(turnLED, OUTPUT);
  
  calibrate();
  
  analogWrite(leftMotorEnablePin, NORMALSPEED);
  analogWrite(rightMotorEnablePin, NORMALSPEED);
}

// calibrate IR sensors 
void calibrate() {
  int time = millis(); 
  int leftSensor, rightSensor;
  int leftPhotoSensor, rightPhotoSensor;
  
  while ((millis() - time) < 3000) {
    leftSensor = analogRead(leftSensorPin);
    rightSensor = analogRead(rightSensorPin);
    leftPhotoSensor = analogRead(leftPhotoSensorPin);
    rightPhotoSensor = analogRead(rightPhotoSensorPin);
    
    Serial.print(leftSensor);
    Serial.print("\t");
    Serial.print(rightSensor);
    Serial.print("\n");
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
int CheckSensors(boolean type) {
  
  // Type: 1 for reading IR; 0 for reading photoresistors
  
  int time;
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
  
//  Serial.print(leftSensor);
//  Serial.print("\t");
//  Serial.print(leftSensorMapped);
//  Serial.print("\t");
//  Serial.print(rightSensor);
//  Serial.print("\t");
//  Serial.print(rightSensorMapped);
//  Serial.print("\n");
  
  if ((leftSensorMapped > 50) and (rightSensorMapped < 50)) {
    // left sensor touches the line while right sensor stays in
    return -1;
  }
  if ((rightSensorMapped > 50) and (leftSensorMapped < 50))
    // right sensor touches the line while left sensor stays in
    return 1;
  if ((leftSensorMapped > 50) and (rightSensorMapped > 50))
    // both sensors touch the line -> intersection
    return 2;
  // no sensor touches line, keep current motion
  return 0;
}

// adjust motor speeds to achieve straight motion, turn after arriving at an intersection
// uses LED to indicate sensor reading results: HIGH: touch line LOW: in white region
void LineFollow(int dist, int dir) {
  
  int drivingInst, photoInst;
  byte count = 0;
  int inttime = millis();
  
  while (true) {
    
    drivingInst = CheckSensors(1);
    photoInst = CheckSensors(0);
    
    if ((drivingInst != photoInst) && (drivingInst != 0) && (photoInst != 0)) {
      Serial.println("wrong");
      continue;
    }
    
    if ((drivingInst == 0) && (photoInst == 0)) {
      Serial.println("Moving forward");
      digitalWrite(leftLED, LOW);
      digitalWrite(rightLED, LOW);
      
      analogWrite(leftMotorEnablePin, NORMALSPEED);
      analogWrite(rightMotorEnablePin, NORMALSPEED);
         
    } else if (drivingInst ==0) {
      drivingInst = photoInst;
    }
    
    if (drivingInst == -1) {
      // left sensor touches the line, adjust to the left   
      digitalWrite(leftLED, HIGH);
      digitalWrite(rightLED, LOW);
      Serial.println("going left");
      analogWrite(leftMotorEnablePin, SLOWSPEED);
      analogWrite(rightMotorEnablePin, FASTSPEED);
      
    }
    
    if (drivingInst == 1) {
      // right sensor touches the line, adjust to the right 
      digitalWrite(leftLED, LOW);
      digitalWrite(rightLED, HIGH);
      Serial.println("going right");
      analogWrite(leftMotorEnablePin, FASTSPEED);
      analogWrite(rightMotorEnablePin, SLOWSPEED);
    
    }
    
    if (drivingInst == 2) {
      digitalWrite(leftLED, HIGH);
      digitalWrite(rightLED, HIGH);
      Serial.println("intersection");
      delay(100);
      digitalWrite(leftMotorEnablePin, 0);
      digitalWrite(rightMotorEnablePin, 0);
      if ((millis() - inttime) > 1500) {
        count++;
        inttime = millis();
        Serial.println("Intersection");
        Serial.println(count);
      }
      
      if (count == dist) {
        Serial.print("Distance reached");
        // make a turn
        Turn(dir);
        // restore forward motion before returning
        digitalWrite(leftMotorEnablePin, LOW);
        digitalWrite(rightMotorEnablePin, LOW);
        delay(300);
        digitalWrite(leftMotorCtrlPin1, HIGH);
        digitalWrite(leftMotorCtrlPin2, LOW);
        digitalWrite(rightMotorCtrlPin1, HIGH);
        digitalWrite(rightMotorCtrlPin2, LOW);
        return;
      }
    }
    
  }
}

void Turn(byte dir) {
  
   int state = 0;
  
   switch (dir) {
       case 1: 
       // Turning left
           digitalWrite(leftMotorEnablePin, 0);
           digitalWrite(rightMotorEnablePin, 0);
           digitalWrite(turnLED, HIGH);
//           delay(100);
           digitalWrite(rightMotorCtrlPin1, HIGH);
           digitalWrite(rightMotorCtrlPin2, LOW);
           digitalWrite(leftMotorCtrlPin1, LOW);
           digitalWrite(leftMotorCtrlPin2, HIGH);
           analogWrite(leftMotorEnablePin, NORMALSPEED);
           analogWrite(rightMotorEnablePin, NORMALSPEED);
           delay(2500);
//           analogWrite(leftMotorEnablePin, 0);
//           digitalWrite(rightMotorCtrlPin1, HIGH);
//           digitalWrite(rightMotorCtrlPin2, LOW);
//           delay(1000);
//           Serial.println("DONE");
//           while(true) {
//             Serial.println("turning");
//             //state = CheckSensors(0);
//             Serial.println(state);
//             if ((CheckSensors(1) == -1 || CheckSensors(1) == 2)){
//               while (CheckSensors(1) != 1){}
//               
//               Serial.println("ASKDJALFJS");
//               break;
//             }
//           }
//           
//           digitalWrite(turnLED, LOW);
           break;
       case 2:
       // Turning right
//           digitalWrite(leftMotorEnablePin, LOW);
//           digitalWrite(rightMotorEnablePin, LOW);
//           delay(500);
//           digitalWrite(rightMotorCtrlPin1, LOW);
//           digitalWrite(rightMotorCtrlPin2, HIGH);
//           digitalWrite(leftMotorCtrlPin1, HIGH);
//           digitalWrite(leftMotorCtrlPin2, LOW);
//           analogWrite(leftMotorEnablePin, NORMALSPEED);
//           analogWrite(rightMotorEnablePin, SLOWSPEED);
//           // Time to make a 90 degree turn
//           delay(1500);
           digitalWrite(leftMotorEnablePin, 0);
           digitalWrite(rightMotorEnablePin, 0);
           digitalWrite(turnLED, HIGH);
//           delay(100);
           digitalWrite(rightMotorCtrlPin1, LOW);
           digitalWrite(rightMotorCtrlPin2, HIGH);
           digitalWrite(leftMotorCtrlPin1, HIGH);
           digitalWrite(leftMotorCtrlPin2, LOW);
           analogWrite(leftMotorEnablePin, NORMALSPEED);
           analogWrite(rightMotorEnablePin, NORMALSPEED);
           delay(800);
           break;
   }
//   digitalWrite(leftMotorCtrlPin1, HIGH);
//   digitalWrite(leftMotorCtrlPin2, LOW);
//   digitalWrite(rightMotorCtrlPin1, HIGH);
//   digitalWrite(rightMotorCtrlPin2, LOW);
   return;
}

int dist = 3;
int dir = 1;
  
void loop() {
  
  digitalWrite(leftMotorCtrlPin1, HIGH);
  digitalWrite(leftMotorCtrlPin2, LOW);
  digitalWrite(rightMotorCtrlPin1, HIGH);
  digitalWrite(rightMotorCtrlPin2, LOW);
  
  LineFollow(2, 1);
  LineFollow(1, 2);
  
  mySweeper.write(-110);
  
  delay(2000);
  
  digitalWrite(leftMotorCtrlPin1, HIGH);
  digitalWrite(leftMotorCtrlPin2, LOW);
  digitalWrite(rightMotorCtrlPin1, HIGH);
  digitalWrite(rightMotorCtrlPin2, LOW);
  
  analogWrite(leftMotorEnablePin, 200);
  analogWrite(rightMotorEnablePin, 200);
  
  delay(3000);
  
  analogWrite(leftMotorEnablePin, 0);
  analogWrite(rightMotorEnablePin, 0);
  
  mySweeper.write(110);
  delay(1000);
 
  digitalWrite(leftMotorCtrlPin1, LOW);
  digitalWrite(leftMotorCtrlPin2, HIGH);
  digitalWrite(rightMotorCtrlPin1, LOW);
  digitalWrite(rightMotorCtrlPin2, HIGH);
  analogWrite(leftMotorEnablePin, 200);
  analogWrite(rightMotorEnablePin, 200);
  
  delay(2000);
  
  digitalWrite(leftMotorEnablePin, 0);
  digitalWrite(rightMotorEnablePin, 0);
  delay(100000);
  //LineFollow(2,dir);
//  Serial.println("DONE :)");
//  digitalWrite(leftMotorEnablePin, 0);
//  digitalWrite(rightMotorEnablePin, 0);
//  
//  delay(5000);
  /*LineFollow(dist,dir);
    
  Serial.println("DONE :)");
  digitalWrite(leftMotorEnablePin, 0);
  digitalWrite(rightMotorEnablePin, 0);
  delay(5000);*/
}


