#pragma once
#include "AbstractSensor.h"
#include "main.h"
#include <MCP3008.h>

#ifndef Arduino_h
#include <Arduino.h>
#endif

extern const int PYRANOMETER_CS_PIN;
extern const int SCK_PIN;
extern const int MISO_PIN;
extern const int MOSI_PIN;


/**
 * \class pyranometer


 * \brief a simple interface to an external ADC sensor.
 *
 * Our pyranometer requires an external adc to work with the esp32 but it should
 * behave just like any other sensor. This ensures it acts according to
 * established design criteria.
 */


class PyranometerSensor: public AbstractSensor {
public:

  /**
  * \brief Set up the pyranometer.
  *
  * \return status The function exit state.
  */
  int8_t setup();

  /**
  * \brief Read from the pyranometer.
  *
  *
  * \param address The memory location where ourput will be written.
  *
  * \return len The length written into memory at `address`.
  */
  uint8_t read(uint8_t* address);

  /**
  * \brief Delete adc variable created in setup.
  *
  * \return status The function exit state.
  */
  int8_t end();

private:

  /**
 * \var MCP3008
 *
 * \brief Gives access to external adc.
 */
 MCP3008* adc;
};
