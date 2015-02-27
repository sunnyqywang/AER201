// pin assignments
const int leftMotorCtrlPin1 = 7;
const int leftMotorCtrlPin2 = 13;
const int leftMotorEnablePin = 6;

const int rightMotorCtrlPin1 = 8;
const int rightMotorCtrlPin2 = 12;
const int rightMotorEnablePin = 5;

//left A3
//right A2
const int leftSensorPin = A4;
const int rightSensorPin = A5;

const int leftLED = 11;
const int rightLED = 10;
const int turnLED = 9;

// initialize global variables
int maxLeft = 0;
int minLeft = 1023;
int maxRight = 0;
int minRight = 1023;

const int SLOWSPEED = 100;
const int FASTSPEED = 255;
const int NORMALSPEED = 255;

void setup() {
  
  Serial.begin(9600);
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);

  
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
  
  while ((millis() - time) < 3000) {
    leftSensor = analogRead(leftSensorPin);
    rightSensor = analogRead(rightSensorPin);
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
  }
  
  Serial.println("Calibration done\n");
  Serial.print(maxLeft);
  Serial.print("\t");
  Serial.print(minLeft);
  Serial.print("\n");
  Serial.print(maxRight);
  Serial.print("\t");
  Serial.print(minRight);
  Serial.print("\n");
  
  // LEDs indicate calibration is done
  digitalWrite(leftLED, HIGH);
  digitalWrite(rightLED, HIGH);
  delay(2000);
  digitalWrite(leftLED, LOW);
  digitalWrite(rightLED, LOW);
  
  return;
}

// get sensor readings and make adjustment decisions
int CheckSensors() {
  
  int time;
  int leftSensor = analogRead(leftSensorPin);
  int rightSensor = analogRead(rightSensorPin);
 
  int leftSensorMapped = map(leftSensor, minLeft, maxLeft, 0, 100);
  int rightSensorMapped = map(rightSensor, minRight, maxRight, 0, 100);
  
  Serial.print(leftSensor);
  Serial.print("\t");
  Serial.print(leftSensorMapped);
  Serial.print("\t");
  Serial.print(rightSensor);
  Serial.print("\t");
  Serial.print(rightSensorMapped);
  Serial.print("\n");
  
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
  
  int drivingInst;
  byte count = 0;
  int inttime = millis();
  
  while (true) {
    
    drivingInst = CheckSensors();
    
    if (drivingInst == -1) {
      Serial.println("going left");
      // left sensor touches the line, adjust to the left   
      digitalWrite(leftLED, HIGH);
      digitalWrite(rightLED, LOW);
  
      analogWrite(leftMotorEnablePin, FASTSPEED);
      analogWrite(rightMotorEnablePin, SLOWSPEED);
      
    }
    
    if (drivingInst == 1) {
      // right sensor touches the line, adjust to the right 
      digitalWrite(leftLED, LOW);
      digitalWrite(rightLED, HIGH);
  
      analogWrite(leftMotorEnablePin, SLOWSPEED);
      analogWrite(rightMotorEnablePin, FASTSPEED);
    
    }
    
    if (drivingInst == 2) {
      digitalWrite(leftLED, HIGH);
      digitalWrite(rightLED, HIGH);
      /*digitalWrite(leftMotorEnablePin, 0);
      digitalWrite(rightMotorEnablePin, 0);
      delay(1000);*/
      if ((millis() - inttime) > 2000) {
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
        /*digitalWrite(leftMotorEnablePin, LOW);
        digitalWrite(rightMotorEnablePin, LOW);
        delay(500);*/
        digitalWrite(leftMotorCtrlPin1, HIGH);
        digitalWrite(leftMotorCtrlPin2, LOW);
        digitalWrite(rightMotorCtrlPin1, HIGH);
        digitalWrite(rightMotorCtrlPin2, LOW);
        return;
      }
    }
    
    if (drivingInst == 0) {
      digitalWrite(leftLED, LOW);
      digitalWrite(rightLED, LOW);
      
      analogWrite(leftMotorEnablePin, NORMALSPEED);
      analogWrite(rightMotorEnablePin, NORMALSPEED);
  
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
           //delay(500);
           digitalWrite(rightMotorCtrlPin1, HIGH);
           digitalWrite(rightMotorCtrlPin2, LOW);
           digitalWrite(leftMotorCtrlPin1, LOW);
           digitalWrite(leftMotorCtrlPin2, HIGH);
           analogWrite(leftMotorEnablePin, NORMALSPEED);
           analogWrite(rightMotorEnablePin, NORMALSPEED);
           
           delay(300);
           while(true) {
             state = CheckSensors();
             Serial.println(state);
             if ((state == -1) )
               break;
           }
           
           digitalWrite(turnLED, LOW);
           break;
       case 2:
       // Turning right
           digitalWrite(leftMotorEnablePin, LOW);
           digitalWrite(rightMotorEnablePin, LOW);
           delay(500);
           digitalWrite(rightMotorCtrlPin1, LOW);
           digitalWrite(rightMotorCtrlPin2, HIGH);
           digitalWrite(leftMotorCtrlPin1, HIGH);
           digitalWrite(leftMotorCtrlPin2, LOW);
           analogWrite(leftMotorEnablePin, NORMALSPEED);
           analogWrite(rightMotorEnablePin, SLOWSPEED);
           // Time to make a 90 degree turn
           delay(1500);
           break;
   }
   return;
}

int dist = 2;
int dir = 1;
  
void loop() {
  
  digitalWrite(leftMotorCtrlPin1, HIGH);
  digitalWrite(leftMotorCtrlPin2, LOW);
  digitalWrite(rightMotorCtrlPin1, HIGH);
  digitalWrite(rightMotorCtrlPin2, LOW);
  
  LineFollow(dist, dir);
  
  Serial.println("DONE :)");
  digitalWrite(leftMotorEnablePin, 0);
  digitalWrite(rightMotorEnablePin, 0);
  delay(5000);
  LineFollow(dist,dir);
    
  Serial.println("DONE :)");
  digitalWrite(leftMotorEnablePin, 0);
  digitalWrite(rightMotorEnablePin, 0);
  delay(5000);
}


