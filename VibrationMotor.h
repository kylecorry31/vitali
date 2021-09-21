#ifndef VibrationMotor_H
#define VibrationMotor_H

#include <Arduino.h>

class VibrationMotor {
    public:
        VibrationMotor(int pin);
        void begin();
        void on(int power);
        void off();
    private:
        int pin;
};

#endif
