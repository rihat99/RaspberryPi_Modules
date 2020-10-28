#include "Servo.h"

#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

using namespace std;

namespace PI {

    Servo::Servo(int pinNum) :
            servoPin(pinNum) {
        softPwmCreate(servoPin, 0, 200);
    }

    double Map(double value, double fromLow, double fromHigh, double toLow, double toHigh) {
        return (toHigh - toLow) * (value - fromLow) / (fromHigh - fromLow) + toLow;
    }

    void Servo::setAngle(double angle) {
        if (angle < 0)
            angle = 0;
        if (angle > 180)
            angle = 180;
        softPwmWrite(servoPin, Map(angle, 0, 180, 5, 25));
    }

    void Servo::loopRotate(int from, int to, int speedDelay, int stopDelay) {
        if (from < 0) from = 0;
        if (to > 180) to = 180;
        int i;

        while (true) {
            for (i = from; i < to + 1; i++) { // Let servo rotate from 0 to 180.
                setAngle(i);
                delay(speedDelay);
            }
            delay(stopDelay);
            for (i = to; i >= from; i--) { // Let servo rotate from 180 to 0.
                setAngle(i);
                delay(speedDelay);
            }
            delay(stopDelay);
        }
    }

}//PI