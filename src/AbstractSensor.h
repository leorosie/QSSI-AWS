/** Base class for all sensors.
*
*  All sensors will adhere to a simple guideline:
*   - they must be able to set up
*   - they must be able to read
*/

#pragma once

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
  *   NOTE: another (possibly better) way of doing this is to pass in
  *         a pointer (int8_t*), write in our bytes, then pass back
  *         the length of the byte string (e.g. float -> 4 bytes).
  *         As written, we may run the risk of screwing up data writes
  *         since we're unsure about where to stop reading (?)
  *
  *   @return pointer to first Byte
  */
  virtual uint8_t* read() = 0;
};
