#pragma once
#include "AbstractSensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "main.h"
#include "utils.h"

extern const int ONE_WIRE_BUS;

/**
* \var MAX_TS_RETRIES
* \brief Number of times we attempt to read the TemperatureSensor before
* we return its error code instead.
*/
const int MAX_TS_RETRIES = 100;

/**
* \var TS_POWERON_ERROR
* \brief Default error thrown when TemperatureSensor first powers up.
*/
const float TS_POWERON_ERROR = 85.0;

/**
* \var TS_READ_ERROR
* \brief Error thrown by TemperatureSensor when device inaccessible for read.
*/
const float TS_READ_ERROR = -127.0;

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
  * This sensor has some odd behavior in the prototype where it returns errors
  * for a while after it is first powered on by the transistor-regulated ground.
  * As such, we poll the device for temperatures until it gives us a number that
  * isn't one of the error codes defined above (85 or -127) or it runs out of
  * tries (MAX_TS_RETRIES).
  */
  uint8_t read(uint8_t* address);

private:

  /**
   * \var DallasTemperature dt_sensor
   * \brief Gives access to information over the OneWire bus.
   */
  DallasTemperature* dt_sensor;

  /**
   * \var OneWire oneWire
   * \brief Handles addressing of sensors.
   */
  OneWire* oneWire;
};
