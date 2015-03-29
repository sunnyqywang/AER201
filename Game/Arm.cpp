//
//  Arm.cpp
//  
//
//  Created by Qingyi Wang on 2015-03-24.
//
//

#include "Arm.h"
#include "Data.h"
#include <Servo.h>

extern Servo myArm;
extern Servo mySweeper;

void LiftArmHalfWay() {
    
    myArm.write(ARMHORIZONTAL+10);
    delay(200);
    myArm.write(ARMHORIZONTAL+25);
    delay(200);
    myArm.write(ARMHORIZONTAL+40);

}

void DropArmHalfWay() {
  
  myArm.write(ARMHORIZONTAL+85);
  delay(400);
  myArm.write(ARMHORIZONTAL+70);
  delay(400);
  myArm.write(ARMHORIZONTAL+60);
  
}

void ArmDrop() {
    
    myArm.write(ARMHORIZONTAL+20);
    delay(500);
    myArm.write(ARMHORIZONTAL+10);
    delay(500);
    myArm.write(ARMHORIZONTAL+5);
    delay(500);
    myArm.write(ARMHORIZONTAL);
    
}

void ArmAllTheWay() {
    
    myArm.write(ARMHORIZONTAL+60);
    delay(200);
    myArm.write(ARMHORIZONTAL+80);
    delay(200);
    myArm.write(ARMHORIZONTAL+90);
    
}

void CloseSweeper() {
    
    mySweeper.write(SWEEPERCLOSED);
    
}


void OpenSweeper() {
    
    mySweeper.write(SWEEPEROPEN);
    
}
