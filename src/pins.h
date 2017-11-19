#pragma once

#include <Arduino.h>

/** Set the values for our pins to be used elsewhere.
*
*/

/** \var WAKE_PIN
*   \brief Pin that receives signal to wake microcontroller.
*/

/** \var SONIC_RANGER_BUS
*   \brief Pin that receives pulse signal from sonic range finder.
*/

/** \var ONE_WIRE_BUS
*   \brief Pin used in communication with one-wire temperature sensor.
*/

/*
* TODO: add pins for SD card, pyranometer, camera
*/

const gpio_num_t WAKE_PIN = GPIO_NUM_39;
const int SONIC_RANGER_BUS = 12;
const int ONE_WIRE_BUS = 14;

const int SCK_PIN = 18;
const int MISO_PIN = 19;
const int MOSI_PIN = 23;
