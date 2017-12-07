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

/** \var PYRANOMETER_CS_PIN
*   \brief Pin used in communication with external adc and pyranometer.
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


const gpio_num_t WAKE_PIN = GPIO_NUM_39;
//const gpio_num_t FLUSH_NVS_SWITCH = GPIO_NUM_25;
//const gpio_num_t WIFI_STATION_SWITCH = GPIO_NUM_32;
const int FLUSH_NVS_SWITCH = 25;
const int WIFI_STATION_SWITCH = 32;
const int SONIC_RANGER_BUS = 12;
const int ONE_WIRE_BUS = 14;
const int PYRANOMETER_CS_PIN = 13;

const int SCK_PIN = 18;
const int MISO_PIN = 19;
const int MOSI_PIN = 23;
const int SENSOR_POWER_BUS = 27;
const int SD_CARD_1_POWER_BUS = 26;
const int SD_CARD_2_POWER_BUS = 15;
const int SD_CARD_1_SS = 17;
const int SD_CARD_2_SS = 4;
const int PYRO_ADC_IN_1 = 36;
const int PYRO_ADC_IN_2 = 37;
const int FLUSH_NVS_LED = 33;
