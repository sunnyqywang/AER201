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
    myArm.write(ARMHORIZONTAL+35);
    delay(200);
    myArm.write(ARMHORIZONTAL+50);
    delay(200);
    myArm.write(ARMHORIZONTAL+63);

}

void DropArmHalfWay() {
  
  myArm.write(ARMHORIZONTAL+85);
  delay(400);
  myArm.write(ARMHORIZONTAL+75);
  delay(400);
  myArm.write(ARMHORIZONTAL+63);
  
}

void ArmDrop() {
    
    myArm.write(ARMHORIZONTAL+40);
    delay(300);
    myArm.write(ARMHORIZONTAL+20);
    delay(500);
    myArm.write(ARMHORIZONTAL+10);
    delay(500);
    myArm.write(ARMHORIZONTAL+5);
    delay(500);
    myArm.write(ARMHORIZONTAL);
    
}

void ArmAllTheWay() {
    
    myArm.write(ARMHORIZONTAL+63);
    delay(200);
    myArm.write(ARMHORIZONTAL+75);
    delay(200);
    myArm.write(ARMHORIZONTAL+85);
    
}

void CloseSweeper() {
    
    mySweeper.write(SWEEPERCLOSED);
    
}


void OpenSweeper() {
    
    mySweeper.write(SWEEPEROPEN);
    
}
