//
// Created by 宋 奎熹 on 2017/10/29.
//

#include <iostream>
#include "GPIOlib.h"

#define M_PI                3.1415926
#define WHEEL_AXIS_DISTANCE 150 // in mm
#define MAX_SPEED           30
#define T_INTERVAL          100 // in ms
#define INITIAL_SPEED       10

using namespace std;
using namespace GPIO;

void test();

int main() {
    test();
    return 0;
}

void test() {
    init();
    
    int readingLeft, readingRight;
    
    int leftSpeed  = INITIAL_SPEED;
    int rightSpeed = INITIAL_SPEED;
    
    turnTo(0);
    
    leftSpeed = INITIAL_SPEED;
    rightSpeed = INITIAL_SPEED;

    double leftTotalDistance = 0.0;
    double rightTotalDistance = 0.0;

    int isLeftFaster = 1;
    controlLeft(FORWARD, leftSpeed);
    controlRight(FORWARD, rightSpeed);

    for (int i = 0; i < 600; ++i) {
       
        resetCounter();
        delay(T_INTERVAL);
        getCounter(&readingLeft, &readingRight);
        
        if (readingLeft == -1 || readingRight == -1) {
            printf("Error!\n");
            continue;
        }

        double distanceLeft = readingLeft * 63.4 * M_PI / 390;
        double distanceRight = readingRight * 63.4 * M_PI / 390;

//        double realSpeedLeft = distanceLeft / T_INTERVAL;
//        double realSpeedRight = distanceRight / T_INTERVAL;
        
//        double deltaDistance = distanceRight - distanceLeft;
//        isLeftFaster /= 2;
//        isLeftFaster = -deltaDistance;
        

        leftTotalDistance += distanceLeft;
        rightTotalDistance += distanceRight;

//        if (realSpeedLeft < INITIAL_SPEED) {
//            leftSpeed += (int)((INITIAL_SPEED - realSpeedLeft) / 2.0);
//            if (leftSpeed >= MAX_SPEED) {
//                leftSpeed = MAX_SPEED;
//            }
//        } else {
//            leftSpeed -= (int)((realSpeedLeft - INITIAL_SPEED) / 2.0);
//        }
//
//        if (realSpeedRight < INITIAL_SPEED) {
//            rightSpeed += (int)((INITIAL_SPEED - realSpeedRight) / 2.0);
//            if (rightSpeed >= MAX_SPEED) {
//                rightSpeed = MAX_SPEED;
//            }
//        } else {
//            rightSpeed -= (int)((realSpeedRight - INITIAL_SPEED) / 2.0);
//        }
        
//        printf("%f, %f, %d, %d\n", distanceLeft, distanceRight, leftSpeed, rightSpeed);
        
        /**
        if (isLeftFaster < 0) {
            if (leftSpeed < 0.95 * MAX_SPEED) {
                leftSpeed++;
            } else {
                rightSpeed -= 2;
            }

            printf("Left %f, %f, %d, %d\n", distanceLeft, distanceRight, leftSpeed, rightSpeed);

        } else if (isLeftFaster > 0) {
            if (rightSpeed < 0.95 * MAX_SPEED) {
                rightSpeed++;
            } else {
                leftSpeed -= 2;
            }

            printf("Right  %f, %f, %d, %d\n", distanceLeft, distanceRight, leftSpeed, rightSpeed);
        }
         */
        
        if (isLeftFaster < 0) {
            
            turnTo(10);
            delay(500);
            turnTo(-10);
            delay(500);
            
            isLeftFaster = 1;

            printf("Left %f, %f, %d, %d\n", distanceLeft, distanceRight, leftSpeed, rightSpeed);
        } else if (isLeftFaster > 0) {

            turnTo(-30);
            delay(1000);
            turnTo(10);
            delay(500);
            
            isLeftFaster = -1;

            printf("Right  %f, %f, %d, %d\n", distanceLeft, distanceRight, leftSpeed, rightSpeed);
        }

        /**
        if (leftSpeed < MAX_SPEED) {
            leftSpeed++;
        }
        if (rightSpeed < MAX_SPEED) {
            rightSpeed++;
        }
         */

        /**
        //TODO: 此处参数需要调整
        if (rightTotalDistance - leftTotalDistance > 0.25 * WHEEL_AXIS_DISTANCE) {
            if (leftSpeed < MAX_SPEED) {
                leftSpeed++;
            } else {
                rightSpeed--;
            }
        }
        if (leftTotalDistance - rightTotalDistance > 0.25 * WHEEL_AXIS_DISTANCE) {
            if (rightSpeed < MAX_SPEED) {
                rightSpeed++;
            } else {
                leftSpeed--;
            }
        }
         */

    }

    printf("Left wheel moved %.2lf cm in total, right wheel moved %.2lf cm in total.\n", leftTotalDistance / 10,
           rightTotalDistance / 10);

    stopLeft();
    stopRight();
}
