#pragma once
#include "AbstractSensor.h"
#include "main.h"

#ifndef Arduino_h
#include <Arduino.h>
#endif

extern const int SONIC_RANGER_BUS;

/**
 * \class SonicRangeSensor
 * \brief a simple interface to a pulse-measuring sensor.
 *
 * Our new sonic range sensor is fairly simple to use but it should
 * behave just like any other sensor. This ensures it acts according to
 * established design criteria.
 */
class SonicRangeSensor: public AbstractSensor {
public:

  /**
  * \brief Set up the sonic ranger.
  *
  * \return status The function exit state.
  */
  int8_t setup();

  /**
  * \brief Read from the sonic ranger.
  *
  * Read from the SRS, format the data, and give it back to main.
  * Formatting is an issue for utils.h, so this method is actually
  * pretty simple.
  *
  * \param address The memory location where ourput will be written.
  *
  * \return len The length written into memory at `address`.
  */
  uint8_t read(uint8_t* address);
};
