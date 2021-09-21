#include "Barometer.h"

Barometer::Barometer(){
}

void Barometer::begin(){
    while(!barometer_.begin(0x76));
}

double Barometer::getPressure(){  
    return barometer_.readPressure() / 100.0;
}
