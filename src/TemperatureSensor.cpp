#include "TemperatureSensor.h"

int8_t TemperatureSensor::setup(){
  int8_t status = 0;
  this->oneWire = new OneWire(ONE_WIRE_BUS);
  this->dt_sensor = new DallasTemperature(oneWire);
  pinMode(ONE_WIRE_BUS, INPUT);
  dt_sensor->begin();
  return(status);
}

uint8_t TemperatureSensor::read(uint8_t* address){
  float tempC;
  uint8_t error_count = 0;
  do {
    this->dt_sensor->requestTemperatures();
    float tempC = this->dt_sensor->getTempCByIndex(0);
    delay(10);
    ++error_count;
  } while ( ((abs(tempC - TS_POWERON_ERROR) <= 0.01 ) ||
      (abs(tempC - TS_READ_ERROR) <= 0.01)) &&
      error_count <= MAX_TS_RETRIES);
  uint8_t len;
  len = float_to_bytes(address, tempC);
  return(len);
}
