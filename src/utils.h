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
    uint8_t temp_array[4];
  } u;
  u.float_bytes = float_val;
  memcpy(address, u.temp_array, 4);
  //return(sizeof(u.temp_array));
  return(u.float_bytes);
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
    uint8_t temp_array[4];
  } u;
  float f;
  memcpy(u.temp_array, address, 4);
  f = u.float_bytes;
  return(f);
}

inline uint8_t long_to_bytes(uint8_t* address, long long_val){
  union {
    long long_bytes;
    uint8_t sonic_array[8];
  } u;
  u.long_bytes = long_val;
  memcpy(address, u.sonic_array, 8);
  return(sizeof(u.sonic_array));
  //LOOK INTO:
  //return(u.long_bytes); QC and returns weird number for sonic ranger
}

inline long bytes_to_long(uint8_t* address){
  union {
    long long_bytes;
    uint8_t sonic_array[8];
  } u;
  long l;
  memcpy(u.sonic_array, address, 8);
  l = u.long_bytes;
  return(l);
}
