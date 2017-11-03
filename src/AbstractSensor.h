/**
*  \file AbstractSensor.h
*  \brief Base class for all sensors.
*
*  All sensors will adhere to a simple guideline:
*   - they must be able to set up
*   - they must be able to read
*/

#pragma once

#include <stdint.h>


class AbstractSensor {
public:

  /**
  *   \brief Set up a sensor.
  *
  *   Required method: set up the sensor.
  *   Do whatever this sensor needs to be ready for operation. This may include
  *   initializing other libraries, routing pins, etc.
  *
  *   \return Status code (-1 -> error, 0 -> success, other)
  */
  virtual int8_t setup() = 0;

  /**
  *   \brief Read from a sensor.
  *
  *   Required method: read from the sensor
  *   Read from the initialized sensor and return its data.
  *
  *   \param address: pointer to memory where output will be stored
  *                   as bytes; this is to ensure consistency.
  *
  *   \return uint8_t length of byte string that needs to be read.
  */
  virtual uint8_t read(uint8_t* address) = 0;
};
