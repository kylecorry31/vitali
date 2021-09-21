#include "VibrationMotor.h"

VibrationMotor::VibrationMotor(int pin)
{
  this->pin = pin;
}

void VibrationMotor::begin()
{
  pinMode(pin, OUTPUT);
}

void VibrationMotor::on(int power)
{
  if (power >= 255)
  {
    digitalWrite(pin, HIGH);
  } else if (power <= 0)
  {
    off();
  }
  else 
  {
    analogWrite(pin, power);
  }
}

void VibrationMotor::off()
{
  digitalWrite(pin, LOW);
}
