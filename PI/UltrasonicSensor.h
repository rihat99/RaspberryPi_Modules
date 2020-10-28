#pragma once

namespace PI {

    struct Unit {
        double in_metres;

        Unit(double data);

        double meters() const;

        double centimeters() const;

        double inches() const;
    };

    class UltrasonicSensor {
    public:
        UltrasonicSensor(int trig_, int echo_);

        Unit measure() const;

    private:
        int trig;
        int echo;
    };

}//PI
