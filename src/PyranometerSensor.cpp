#include "PyranometerSensor.h"



int8_t PyranometerSensor::setup(){
  int8_t status = 0;
  MCP3008* adc = new MCP3008(SCK_PIN, MOSI_PIN, MISO_PIN, PYRANOMETER_CS_PIN);
  this->adc = adc;
  return(status);
}

int8_t PyranometerSensor::end(){
  int8_t status = 0;
  delete this->adc;
  return(status);
}

uint8_t PyranometerSensor::read(uint8_t* address){
  uint8_t len = 1;
  int red_analog = adc->readADC(0);
  int black_analog = adc->readADC(1);
  //While statements to handle wrap around of ints
  while (red_analog > 1023) {
    red_analog = red_analog - 1023;
  }
  while (black_analog > 1023) {
    black_analog = black_analog - 1023;
  }
  //5000 conversion factor for pyranometer
  //0.45 V is reference voltage
  //1023 is max int for output
  int difference = abs(red_analog-black_analog);
  float total_radiation = ((difference*0.45)/1023)*5000;
  *address=total_radiation;
  return(len);
}
