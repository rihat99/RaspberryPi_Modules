#include "UltrasonicSensor.h"

#include "wiringPi.h"
#include <sys/time.h>

using namespace std;

Unit::Unit(double data) : in_metres(data)
{

}

double Unit::meters() const { return in_metres; }

double Unit::centimeters() const { return in_metres * 100.0; }

double Unit::inches() const { return in_metres * 39.3701; }

UltrasonicSensor::UltrasonicSensor(int trig_, int echo_) :
    trig(trig_), echo(echo_)
{
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

Unit UltrasonicSensor::measure() const {
    timeval tv1;
    timeval tv2;
    long time1, time2;
    double dis;

    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    while(!(digitalRead(echo) == 1));
    gettimeofday(&tv1, nullptr);

    while(!(digitalRead(echo) == 0));
    gettimeofday(&tv2, nullptr);

    time1 = tv1.tv_sec * 1000000 + tv1.tv_usec;
    time2  = tv2.tv_sec * 1000000 + tv2.tv_usec;

    dis = (double )(time2 - time1) / 1000000 * 340 / 2;

    return Unit(dis);
}
