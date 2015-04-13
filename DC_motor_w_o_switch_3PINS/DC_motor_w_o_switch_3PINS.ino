// Jan. 23, 2015

// This program controls two DC motors separately

// Needs input on motorEnable and  motorSpeed

// Motor controlPins are reduced using a NAND gate in the circuit

const int controlPin11 = 22; // connected to pin 2 on the H-bridge
const int controlPin12 = 23;
const int enablePin1 = 2;   // connected to pin 1 on the H-bridge

const int controlPin21 = 24;
const int controlPin22 = 25;
const int enablePin2 = 3;

int motorEnabled = 1; // Turns the motor on/off
int motorSpeed = 0; // speed of the motor
int motorDirection = 2;

void setup(){
  // intialize the inputs and outputs
  pinMode(controlPin11, OUTPUT);
  pinMode(controlPin12, OUTPUT);
  pinMode(enablePin1, OUTPUT);

  pinMode(controlPin21, OUTPUT);
  pinMode(controlPin22, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  
  // pull the enable pin LOW to start
  digitalWrite(enablePin1, LOW);
  digitalWrite(enablePin2, LOW);
}

void loop(){
  
  // change the direction the motor spins by talking
  // to the control pins on the H-Bridge
  if (motorDirection == 1) {
    digitalWrite(controlPin11, LOW);
    digitalWrite(controlPin12, HIGH);
    digitalWrite(controlPin21, LOW);
    digitalWrite(controlPin22, HIGH);
  } 
  else {
    digitalWrite(controlPin11, HIGH);
    digitalWrite(controlPin12, LOW);
    digitalWrite(controlPin21, HIGH);
    digitalWrite(controlPin22, LOW);
  } 
  
  // check if the motor is supposed to be on
  //if (motorEnabled == 1) {
    // PWM the enable pin to vary the speed
    analogWrite(enablePin1, 200);
    analogWrite(enablePin2, 190);
    
//    delay(2000);
//    
//    analogWrite(enablePin1, 0);
//    analogWrite(enablePin2, 0);
//    
//    delay(2000);

  //}
  //else { // if the motor is not supposed to be on
    //turn the motor of

  //}
  
}




