#include "SonicRangeSensor.h"


int8_t SonicRangeSensor::setup(){
  int8_t status = 0;
  pinMode(SONIC_RANGER_BUS, INPUT);
  return(status);
}

uint8_t SonicRangeSensor::read(uint8_t* address){
  uint8_t len;
  long pulse_value, mm, inches,meow;
  pulse_value = pulseIn(SONIC_RANGER_BUS, HIGH);
  mm = pulse_value;
  inches = mm / 25.4;
  //Serial.print(mm); //QC long_to_bytes
  //array = reinterpret_cast<uint8_t*>(&mm);
  *address = mm;
  len=long_to_bytes(address,mm);
  Serial.print(len);
  return(len);
}
