#include "PyranometerSensor.h"

int8_t PyranometerSensor::setup(){
  int8_t status = 0;
  pinMode(PYRANOMETER_BUS, INPUT);
  return(status);
}


uint8_t PyranometerSensor::read(uint8_t* address){
  uint8_t len = 1;
  long sensor_output, shortwave_radiation;
  sensor_output=analogRead(PYRANOMETER_BUS);
  shortwave_radiation=sensor_output*5; //Conversion factor for pyranometer
  len=long_to_bytes(address, shortwave_radiation);
  return(len);
}
