/** Base class for all sensors.
*
*  All sensors will adhere to a simple guideline:
*   - they must be able to set up
*   - they must be able to read
*/

//#pragma once

#include <stdint.h>


class AbstractSensor {
public:

  /** Required method: set up the sensor.
  *   Do whatever this sensor needs to be ready for operation. This may include
  *   initializing other libraries, routing pins, etc.
  *
  *   @return Status code (-1 -> error, 0 -> success, other)
  */
  virtual int8_t setup() = 0;

  /** Required method: read from the sensor
  *   Read from the initialized sensor and return its data.
  *
  *   @return pointer to first Byte
  */
  virtual uint8_t* read() = 0;
} ;
