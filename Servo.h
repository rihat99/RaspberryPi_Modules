#pragma once

class Servo {
public:
    explicit Servo(int pinNum);

    void setAngle(int angle);

private:
    int servoPin;
};
