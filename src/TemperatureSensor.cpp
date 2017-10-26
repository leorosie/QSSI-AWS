#include "TemperatureSensor.h"

/**
*
*/
int8_t TemperatureSensor::setup(){
  int8_t status = 0;
  OneWire oneWire(ONE_WIRE_BUS);
  DallasTemperature dt_sensor(&oneWire);
  DeviceAddress insideThermometer;
  pinMode(ONE_WIRE_BUS, INPUT);
  dt_sensor.begin();

  //temperature sensor stuff
  //Serial.print("Found ");
  //Serial.print(dt_sensors.getDeviceCount(), DEC);
  //Serial.println(" devices.");

  if (! this->dt_sensor.getAddress(insideThermometer, 0)) {
    Serial.println("Unable to find address for Device 0");
  }
  return(status);
}

void TemperatureSensor::printTemperature() {
  float tempC = this->dt_sensor.getTempC(insideThermometer);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}

void TemperatureSensor::printAddress() {
  for (uint8_t i = 0; i < 8; i++)
  {
    if (*insideThermometer < 16) Serial.print("0");
    Serial.print(*insideThermometer, HEX);
  }
}

void TemperatureSensor::printAlarms() {
  char temp;
  temp = this->dt_sensor.getHighAlarmTemp(insideThermometer);
  Serial.print("High Alarm: ");
  Serial.print(temp, DEC);
  Serial.print("C/");
  Serial.print(DallasTemperature::toFahrenheit(temp));
  Serial.print("F | Low Alarm: ");
  temp = this->dt_sensor.getLowAlarmTemp(insideThermometer);
  Serial.print(temp, DEC);
  Serial.print("C/");
  Serial.print(DallasTemperature::toFahrenheit(temp));
  Serial.print("F");
}

void TemperatureSensor::printData() {
  printAlarms();
  Serial.print("Device Address: ");
  printAddress();
  Serial.print(" ");
  printTemperature();
  Serial.println();
}

void TemperatureSensor::checkAlarm() {
  if (this->dt_sensor.hasAlarm(insideThermometer))
  {
    Serial.print("ALARM: ");
    printData();
  }
}
