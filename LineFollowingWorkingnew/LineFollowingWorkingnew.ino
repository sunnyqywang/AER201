// pin assignments
const int leftMotorCtrlPin1 = 7;
const int leftMotorCtrlPin2 = 13;
const int leftMotorEnablePin = 6;

const int rightMotorCtrlPin1 = 8;
const int rightMotorCtrlPin2 = 12;
const int rightMotorEnablePin = 5;

const int leftSensorPin = A4;
const int rightSensorPin = A5;

const int leftLED = 11;
const int rightLED = 10;

// initialize global variables
int maxLeft = 0;
int minLeft = 1023;
int maxRight = 0;
int minRight = 1023;

const int SLOWSPEED = 50;
const int FASTSPEED = 110;
const int NORMALSPEED = 80;

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
  
  calibrate();
  
  analogWrite(leftMotorEnablePin, NORMALSPEED);
  analogWrite(rightMotorEnablePin, NORMALSPEED);
}

// calibrate IR sensors 
void calibrate() {
  int time = millis(); 
  int leftSensor, rightSensor;
  
  while ((millis() - time) < 5000) {
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
  delay(4000);
  digitalWrite(leftLED, LOW);
  digitalWrite(rightLED, LOW);
  
  return;
}

// get sensor readings and make adjustment decisions
char CheckSensors() {
  
  int time;
  int leftSensor = analogRead(leftSensorPin);
  int rightSensor = analogRead(rightSensorPin);
 
  // take average value of sensor in 0.01s to make the result more accurate
  /*time = millis();
  while ((millis()-time) < 10) {
    leftSensor = (leftSensor + analogRead(leftSensorPin))/2;
    rightSensor = (rightSensor + analogRead(rightSensorPin))/2;
  }*/
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
  
  if ((leftSensorMapped < 50) and (rightSensorMapped > 50))
    // left sensor touches the line while right sensor stays in
    return -1;
  if ((rightSensorMapped < 50) and (leftSensorMapped > 50))
    // right sensor touches the line while left sensor stays in
    return 1;
  if ((leftSensorMapped < 50) and (rightSensorMapped < 50))
    // both sensors touch the line -> intersection
    return 2;
  // no sensor touches line, keep current motion
  return 0;
}

// adjust motor speeds to achieve straight motion, turn after arriving at an intersection
// uses LED to indicate sensor reading results: HIGH: touch line LOW: in white region
void LineFollow(int dist, int dir) {
  
  char drivingInst = CheckSensors();
  char count = 0;
  
  if (drivingInst == -1) {
    // left sensor touches the line, adjust to the left
   
    digitalWrite(leftLED, HIGH);
    digitalWrite(rightLED, LOW);

    analogWrite(leftMotorEnablePin, SLOWSPEED);
    analogWrite(rightMotorEnablePin, FASTSPEED);
    
  }
  
  if (drivingInst == 1) {
    // right sensor touches the line, adjust to the right
    
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, HIGH);

    analogWrite(leftMotorEnablePin, FASTSPEED);
    analogWrite(rightMotorEnablePin, SLOWSPEED);
  
  }
  
  if (drivingInst == 2) {
    digitalWrite(leftLED, HIGH);
    digitalWrite(rightLED, HIGH);
    digitalWrite(leftMotorEnablePin, 0);
    digitalWrite(rightMotorEnablePin, 0);
    /*
    count++;
    if (count == dist) {
      // make a turn
      Turn(dir);
      // restore forward motion before returning
      digitalWrite(leftMotorEnablePin, LOW);
      digitalWrite(rightMotorEnablePin, LOW);
      delay(500);
      digitalWrite(leftMotorCtrlPin1, HIGH);
      digitalWrite(leftMotorCtrlPin2, LOW);
      digitalWrite(rightMotorCtrlPin1, HIGH);
      digitalWrite(rightMotorCtrlPin2, LOW);
      
      return;
    }*/
  }
  
  if (drivingInst == 0) {
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);
    
    analogWrite(leftMotorEnablePin, NORMALSPEED);
    analogWrite(rightMotorEnablePin, NORMALSPEED);

  }

  /*Serial.print(leftMotorSpeed);
  Serial.print('\t');
  Serial.println(rightMotorSpeed);*/
  
}

void Turn(byte dir) {
  
   switch (dir) {
       case 1: 
           // Turning left
           digitalWrite(leftMotorEnablePin, LOW);
           digitalWrite(rightMotorEnablePin, LOW);
           delay(500);
           digitalWrite(rightMotorCtrlPin1, HIGH);
           digitalWrite(rightMotorCtrlPin2, LOW);
           digitalWrite(leftMotorCtrlPin1, LOW);
           digitalWrite(leftMotorCtrlPin2, HIGH);
           analogWrite(leftMotorEnablePin, NORMALSPEED);
           analogWrite(rightMotorEnablePin, NORMALSPEED);
           // Time to make a 90 degree turn
           delay(1500);
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
           analogWrite(rightMotorEnablePin, NORMALSPEED);
           // Time to make a 90 degree turn
           delay(1500);
   }
   return;
}

int dist = 1;
int dir = 1;
  
void loop() {
  
  digitalWrite(leftMotorCtrlPin1, HIGH);
  digitalWrite(leftMotorCtrlPin2, LOW);
  digitalWrite(rightMotorCtrlPin1, HIGH);
  digitalWrite(rightMotorCtrlPin2, LOW);
  
  LineFollow(dist, dir);
  /*delay(2000);
  Turn(dir);*/
  
}


