#include "AbstractSensor.h"

#ifndef Arduino_h
#include <Arduino.h>
#endif

#define SONIC_RANGER_BUS 12

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
