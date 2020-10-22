#pragma once

class Servo {
public:
    explicit Servo(int pinNum);

    void setAngle(double angle);
    void loopRotate(int from, int to, int speedDelay, int stopDelay);

private:
    int servoPin;
};
