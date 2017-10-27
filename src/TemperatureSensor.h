#pragma once
#include "AbstractSensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "main.h"

extern const int ONE_WIRE_BUS;

/**
 * \class TemperatureSensor
 * \brief Wraps the DallasTemperature lib to simplify readings.
 *
 * The DallasTemperature library gives a lot of powerful tools
 * but it's still kind of tricky to use. This simplifies the
 * function calls for our central application logic.
 */
class TemperatureSensor: public AbstractSensor {
public:

  /**
  * /brief Set up the sensor using its own values.
  *
  * NOTE: if we end up using more sensors we may want to pass in
  *       a OneWire, DallasTemperature, etc object so that other
  *       temperature sensors can all use it...
  */
  int8_t setup();

  /**
  * \brief Read from the sensor and return it in appropriate format.
  *
  * NOTE: see AbstractSensor for discussion on this method.
  */
  uint8_t* read();

  /**
  * \brief Print the temperature in both C and F.
  *
  */
  void printTemperature();

  /**
  * \brief Print the device address of this sensor.
  *
  */
  void printAddress();

  /**
  * \brief Print any alarms set on this sensor.
  *
  */
  void printAlarms();

  /**
  * \brief Print the alarms, address, and temperature.
  *
  */
  void printData();

  /**
  * \brief Print alarm data and more.
  *
  * TODO: figure out why this is here.
  *
  */
  void checkAlarm();

private:

  /**
   * \var DeviceAddress insideThermometer
   *
   * \brief The location on the OneWire bus where this thermometer is found.
   */
  DeviceAddress insideThermometer;

  /**
   * \var DallasTemperature dt_sensor
   *
   * \brief Gives access to information over the OneWire bus.
   */
  DallasTemperature dt_sensor;
};
