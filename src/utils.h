#pragma once
#include <cstring>
#include <stdint.h>

const uint8_t FLOAT_SIZE = sizeof(float);
const uint8_t LONG_SIZE = sizeof(long);

/**
*  \brief Convert a float to an array of bytes.
*
*  \param address The memory location where the float will be written as bytes
*  \param float_val The number which will be written to bytes
*  \return i The length of the byte string (should always be 4)
*
*  This is part of our data writing scheme; we convert everything to bytes
*  then pipe it into a file writer. The union trick here is a little hacky
*  but it's reliable.
*/
inline uint8_t float_to_bytes(uint8_t* address, float float_val){
  union {
    float float_bytes;
    uint8_t temp_array[FLOAT_SIZE];
  } u;
  u.float_bytes = float_val;
  memcpy(address, u.temp_array, FLOAT_SIZE);
  return(sizeof(u.temp_array));
}

/**
*  \brief Convert an array of bytes to a float.
*
*  \param address The memory location of the bytes (_always_ 4).
*  \return f The float we just made.
*
*  this is mostly for debugging purposes; it shouldn't be needed in operation.
*/
inline float bytes_to_float(uint8_t* address){
  union {
    float float_bytes;
    uint8_t temp_array[FLOAT_SIZE];
  } u;
  float f;
  memcpy(u.temp_array, address, FLOAT_SIZE);
  f = u.float_bytes;
  return(f);
}
