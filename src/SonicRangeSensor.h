#pragma once
#include "AbstractSensor.h"
#include "main.h"

#ifndef Arduino_h
#include <Arduino.h>
#endif

extern const int SONIC_RANGER_BUS;

class SonicRangeSensor: public AbstractSensor {
public:

  /** Set up the sonic ranger.
  *
  */
  int8_t setup();

  /** Read from the sonic ranger.
  *   NOTE: see AbstractSensor for discussion on this method.
  *
  */
  uint8_t* read();
};
