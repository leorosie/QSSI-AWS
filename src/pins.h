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

/** \var SENSOR_POWER_BUS
*   \brief Pin used to lift ground from sensors (diable power).
*/

/** \var SD_CARD_1_POWER_BUS
*   \brief Pin used to lift ground from SD card 1.
*/

/** \var SD_CARD_2_POWER_BUS
*   \brief Pin used to lift ground from SD card 2.
*/

/** \var SD_CARD_1_SS
*   \brief Pin to enable slave select on SD card 1.
*/

/** \var SD_CARD_2_SS
*   \brief Pin to enable slave select on SD card 2.
*/

/** \var PYRO_ADC_IN_1
*   \brief Pin #1 of analog-digital converter for pyranometer.
*/

/** \var PYRO_ADC_IN_2
*   \brief Pin #2 of analog-digital converter for pyranometer.
*/

/** \var FLUSH_NVS_SWITCH
*   \brief Pin to force transfer of data from NVS to SD cards.
*/

/** \var FLUSH_NVS_LED
*   \brief Pin to turn on LED, signaling data transfer is underway.
*/

/** \var WIFI_STATION_SWITCH
*   \brief Pin to toggle WIFI station for status information.
*/

/*
* TODO: correct pins for pyranometer as needed; set for camera
*/

const gpio_num_t WAKE_PIN = GPIO_NUM_39;
const int SONIC_RANGER_BUS = 12;
const int ONE_WIRE_BUS = 14;
const int SENSOR_POWER_BUS = 27;
const int SD_CARD_1_POWER_BUS = 26;
const int SD_CARD_2_POWER_BUS = 1;
const int SD_CARD_1_SS = 4;
const int SD_CARD_2_SS = 17;
const int PYRO_ADC_IN_1 = 36;
const int PYRO_ADC_IN_2 = 37;
const int FLUSH_NVS_SWITCH = 25;
const int FLUSH_NVS_LED = 33;
const int WIFI_STATION_SWITCH = 32;
