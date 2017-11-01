//
// Created by 宋 奎熹 on 2017/10/29.
//

#include <iostream>
#include <cmath>

#include "../header/GPIOlib.h"

#define WHEEL_AXIS_DISTANCE 150 // in mm
#define MAX_SPEED 50

using namespace std;
using namespace GPIO;

void test();

int readingLeft, readingRight;

int leftSpeed = 30;
int rightSpeed = 30;

int main() {
    test();
    return 0;
}

void test() {
    init();
    leftSpeed = 30;
    rightSpeed = 30;

    double leftTotalDistance = 0.0;
    double rightTotalDistance = 0.0;

    int isLeftFaster = 0;

    for (int i = 0; i < 60; ++i) {
        controlLeft(FORWARD, leftSpeed);
        controlRight(FORWARD, rightSpeed);

        resetCounter();
        delay(1000);
        getCounter(&readingLeft, &readingRight);
        if (readingLeft == -1 || readingRight == -1) {
            printf("Error!\n");
            continue;
        }

        double distanceLeft = readingLeft * 63.4 * M_PI / 390;
        double distanceRight = readingRight * 63.4 * M_PI / 390;

        double deltaDistance = distanceRight - distanceLeft;
        isLeftFaster /= 2;
        isLeftFaster -= deltaDistance;


        leftTotalDistance += distanceLeft;
        rightTotalDistance += distanceRight;

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

            isLeftFaster += deltaDistance;
        }


        if (leftSpeed < MAX_SPEED) {
            leftSpeed++;
        }
        if (rightSpeed < MAX_SPEED) {
            rightSpeed++;
        }



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

    }

    printf("Left wheel moved %.2lf cm in total, right wheel moved %.2lf cm in total.\n", leftTotalDistance / 10,
           rightTotalDistance / 10);

    stopLeft();
    stopRight();
}
