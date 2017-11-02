#include "SonicRangeSensor.h"

int8_t SonicRangeSensor::setup(){
  int8_t status = 0;
  pinMode(SONIC_RANGER_BUS, INPUT);
  return(status);
}

//TODO: add long->byte[] casting in utils.h and use here!
uint8_t SonicRangeSensor::read(uint8_t* address){
  uint8_t len = 1;
  long pulse_value, mm, inches;
  pulse_value = pulseIn(SONIC_RANGER_BUS, HIGH);
  mm = pulse_value;
  inches = mm / 25.4;
  *address = mm;
  return(len);
}
