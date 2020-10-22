#include "Servo.h"

#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

Servo::Servo(int pinNum):
    servoPin(pinNum)
{
    softPwmCreate(servoPin, 0, 200);
}

long Map(long value,long fromLow,long fromHigh,long toLow,long toHigh) {
    return (toHigh - toLow) * (value - fromLow) / (fromHigh - fromLow) + toLow;
}

void Servo::setAngle(int angle) {
    if(angle < 0)
        angle = 0;
    if(angle > 180)
        angle = 180;
    softPwmWrite(servoPin,Map(angle, 0, 180, 5, 25));
}
