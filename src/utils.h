#pragma once
#include <cstring>
#include <stdint.h>

/**
*  \brief Convert a float to an array of bytes.
*
*  \param address the memory location where the float will be written as bytes
*  \param float_val the number which will be written to bytes
*  \return i the length of the byte string (should always be 4)
*
*/
inline uint8_t float_to_bytes(uint8_t* address, float float_val){
  union {
    float float_bytes;
    uint8_t float_array[4];
  } u;
  u.float_bytes = float_val;
  memcpy(address, u.float_array, 4);
  return(sizeof(u.float_array));
}

/**
*  \brief Convert an array of bytes to a float.
*
*  \param address the memory location of the bytes (_always_ 4)
*  \return f the float
*
*  this is mostly for debugging purposes; it shouldn't be needed in operation.
*/
inline float bytes_to_float(uint8_t* address){
  union {
    float float_bytes;
    uint8_t float_array[4];
  } u;
  float f;
  memcpy(u.float_array, address, 4);
  f = u.float_bytes;
  return(f);
}

/**
*  \brief Convert a long to an array of bytes.
*
*  \param address the memory location where the long will be written as bytes
*  \param long_val the number which will be written to bytes
*  \return i the length of the byte string (should always be 8)
*
*/

inline uint8_t long_to_bytes(uint8_t* address, long long_val){
  union {
    long long_bytes;
    uint8_t long_array[8];
  } u;
  u.long_bytes = long_val;
  memcpy(address, u.long_array, 8);
  return(sizeof(u.long_array));
}

/**
*  \brief Convert an array of bytes to a long.
*
*  \param address the memory location of the long (_always_ 8)
*  \return l the long
*
*/

inline long bytes_to_long(uint8_t* address){
  union {
    long long_bytes;
    uint8_t long_array[8];
  } u;
  long l;
  memcpy(u.long_array, address, 8);
  l = u.long_bytes;
  return(l);
}
