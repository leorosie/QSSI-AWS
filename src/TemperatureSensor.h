#pragma once
#include "AbstractSensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "main.h"

extern const int ONE_WIRE_BUS;

class TemperatureSensor: public AbstractSensor {
public:

  /** Set up the sensor using its own values.
  *   NOTE: if we end up using more sensors we may want to pass in
  *         a OneWire, DallasTemperature, etc object so that other
  *         temperature sensors can all use it...
  */
  int8_t setup();

  /** Read from the sensor and return it in appropriate format.
  *   NOTE: see AbstractSensor for discussion on this method.
  */
  uint8_t* read();

  /** Print the temperature in both C and F.
  *
  */
  void printTemperature();

  /** Print the device address of this sensor.
  *
  */
  void printAddress();

  /** Print any alarms set on this sensor.
  *
  */
  void printAlarms();

  /** Print the alarms, address, and temperature.
  *
  */
  void printData();

  /** Print alarm data and more.
  *   TODO: figure out why this is here.
  *
  */
  void checkAlarm();

private:
  DeviceAddress insideThermometer;
  DallasTemperature dt_sensor;
};
