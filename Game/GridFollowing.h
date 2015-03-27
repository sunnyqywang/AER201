//
//  GridFollowing.h
//  
//
//  Created by Qingyi Wang on 2015-03-04.
//
//

#ifndef ____GridFollowing__
#define ____GridFollowing__

#include <stdio.h>

void ForwardMotion();
void BackwardMotion();
void TurningLeft();
void TurningRight();
void StartMotors();
void StopMotors();
void LineFollow(int, int);
void Turn(int);

#endif /* defined(____GridFollowing__) */

