#include "Barometer.h"
#include "VibrationMotor.h"

Barometer barometer{};
VibrationMotor upMotor{3};
VibrationMotor downMotor{5};

const double maxPressureChange = 4.0;

const long updateInterval = 60L * 1000L;
const int historyLength = 180;

double history[historyLength];
int historySize = 0;
int historyIdx = 0;
long lastTime = 0;

void setup() {
  Serial.begin(9600);
  barometer.begin();
  upMotor.begin();
  downMotor.begin();
  history[0] = barometer.getPressure();
  historySize = 1;
  historyIdx = 0;
  lastTime = millis();
}

void loop() {
  senseTendency();
}

void sensePressure(){
  const double normalPressure = 1013.0;
  const double pressureRange = 30.0;

  double pressure = barometer.getPressure();

  double diff = pressure - normalPressure;
  double absDiff = abs(diff);

  int vibratePower = constrain((int)map(absDiff, 0.0, pressureRange, 20, 255), 0, 255);

  Serial.println(diff);

  if (diff > 0)
  {
    // High
    downMotor.off();
    upMotor.on(vibratePower);
  } else {
    // Low
    upMotor.off();
    downMotor.on(vibratePower);
  } 
}

void senseTendency(){
  double pressure = barometer.getPressure();

   double first;
  
  if (historySize == historyLength){
    // Already full
    first = history[(historyIdx + 1) % historyLength];
  } else {
    first = history[0];
  }

  if (millis() - lastTime >= updateInterval){
    historySize++;
    historySize = min(historySize, historyLength); 
    historyIdx++;
    historyIdx %= historyLength;
    history[historyIdx] = pressure;
    lastTime = millis();
  }

  double tendency = pressure - first;
  double absTendency = abs(tendency);

  Serial.println(tendency);

  int vibratePower = constrain((int)map(absTendency, 0.0, maxPressureChange, 20, 255), 0, 255);

  if (tendency > 0)
  {
    // Increasing
    downMotor.off();
    upMotor.on(vibratePower);
  } else {
    // Decreasing
    upMotor.off();
    downMotor.on(vibratePower);
  } 
}
