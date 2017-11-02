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
  */
  int8_t setup();

  /**
  * \brief Read from the sonic ranger.
  *
  * NOTE: see AbstractSensor for discussion on this method.
  *
  */
  uint8_t read(uint8_t* address);
};
