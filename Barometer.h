#ifndef Barometer_H
#define Barometer_H

#include <Arduino.h>

#include <Adafruit_BME280.h>

class Barometer {
    public:
        Barometer();
        void begin();
        double getPressure();
    private:
        Adafruit_BME280 barometer_{};
};

  #endif
