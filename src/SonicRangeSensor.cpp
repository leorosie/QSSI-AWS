#include "SonicRangeSensor.h"

int8_t SonicRangeSensor::setup(){
  int8_t status = 0;
  pinMode(SONIC_RANGER_BUS, INPUT);
  return(status);
}

uint8_t* SonicRangeSensor::read(){
  long pulse_value, mm, inches;
  pulse_value = pulseIn(SONIC_RANGER_BUS, HIGH);
  mm = pulse_value - 498.0;
  inches = mm / 25.4;
  uint8_t *array;
  array = reinterpret_cast<uint8_t*>(&mm);
  return(array);
}
