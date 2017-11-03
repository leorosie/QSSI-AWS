#pragma once
#include "AbstractSensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "main.h"
#include "utils.h"

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
  uint8_t read(uint8_t* address);

private:

  /**
   * \var DallasTemperature dt_sensor
   *
   * \brief Gives access to information over the OneWire bus.
   */
  DallasTemperature * dt_sensor;

  /**
   * \var OneWire oneWire
   *
   * \brief Handles addressing of sensors.
   */
  OneWire * oneWire;
};
