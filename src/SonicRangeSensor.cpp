#include "SonicRangeSensor.h"

int8_t SonicRangeSensor::setup(){
  int8_t status = 0;
  pinMode(SONIC_RANGER_BUS, INPUT);
  return(status);
}

uint8_t SonicRangeSensor::read(uint8_t* address){
  uint8_t len = 1;
  long pulse_value, mm, inches;
  pulse_value = pulseIn(SONIC_RANGER_BUS, HIGH);
  mm = pulse_value;
  inches = mm / 25.4;
  //array = reinterpret_cast<uint8_t*>(&mm);
  *address = mm;
  return(len);
}
