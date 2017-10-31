//#include "../header/GPIOlib.h"
//#include <iostream>
//
//#define MAX_SPEED 500
//#define DELAY 1000
//
//void test();
//
//int main() {
//    GPIO::init();
//    GPIO::controlLeft(FORWARD, 30);
//    GPIO::controlRight(FORWARD, 30);
//    GPIO::delay(DELAY);
//
//    int leftSpeed, rightSpeed;
//
//    int i = 1;
//    while (i <= 10) {
//        GPIO::getCounter(&leftSpeed, &rightSpeed);
//
//        if (leftSpeed > rightSpeed) {
//            if (leftSpeed >= MAX_SPEED) {
//                GPIO::controlLeft(BACKWARD, rightSpeed);
//            } else {
//                GPIO::controlRight(FORWARD, leftSpeed);
//            }
//        } else if (leftSpeed < rightSpeed) {
//            if (rightSpeed >= MAX_SPEED) {
//                GPIO::controlRight(BACKWARD, leftSpeed);
//            } else {
//                GPIO::controlLeft(FORWARD, rightSpeed);
//            }
//        }
//
//        i++;
//        GPIO::resetCounter();
//        GPIO::delay(DELAY);
//    }
//
//    GPIO::stopLeft();
//    GPIO::stopRight();
//
//    return 0;
//}