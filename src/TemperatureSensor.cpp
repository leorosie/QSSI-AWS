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
  this->dt_sensor->requestTemperatures();
  float tempC = this->dt_sensor->getTempCByIndex(0);
  uint8_t len;
  len = float_to_bytes(address, tempC);
  Serial.println(len);
  return(len);
}
