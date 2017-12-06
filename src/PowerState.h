#pragma once

#include "esp_system.h"
#include "esp_deep_sleep.h"

#include "pins.h"
#include "utils.h"

extern const gpio_num_t WAKE_PIN;
extern const int FLUSH_NVS_SWITCH;
extern const int WIFI_STATION_SWITCH;
//extern const gpio_num_t FLUSH_NVS_SWITCH;
//extern const gpio_num_t WIFI_STATION_SWITCH;

extern const int SONIC_RANGER_BUS;
extern const int ONE_WIRE_BUS;
extern const int PYRO_ADC_IN_1;
extern const int PYRO_ADC_IN_2;

extern const int SENSOR_POWER_BUS;
extern const int SD_CARD_1_POWER_BUS;
extern const int SD_CARD_2_POWER_BUS;
extern const int SD_CARD_1_SS;
extern const int SD_CARD_2_SS;

extern const int FLUSH_NVS_LED;

class PowerState {
public:

  PowerState();

  //~PowerState();

  //NOTE no copy constructor; we will never have 2 states.

  /**
  *   \brief Set the board's power state to mostly off.
  *   \return status Indicates exit status of configuration.
  *
  *   This is mostly used to transition to the next state; by 'zeroing'
  *   everything at once, we don't need to do as much in other states.
  */
  uint8_t enter_basic_state();

  /**
  *   \brief Set the board's power state to read from sensors.
  *   \return status Indicates exit status of configuration.
  *
  *   The state we spend most time in aside from asleep! This turns on the
  *   sensor power bus so that our sensors can read.
  */
  uint8_t enter_sensor_state();

  /**
  *   \brief Set the board's power state to write an SD card.
  *   \param number The number of the SD card to use (1 or 2 for now).
  *   \return status Indicates exit status of configuration.
  *
  *   This should be turned on for an SD card before writing out from NVS.
  *   I'd like to make it more general (for n cards...) but that's harder.
  */
  uint8_t enter_SD_card_write_state(uint8_t number);

  /**
  *   \brief Set the board's power state to broadcast WiFi.
  *   \return status Indicates exit status of configuration.
  *
  *   We need to broadcast information so we will make a local wifi access
  *   point and broadcase a simple html page with some data.
  */
  uint8_t enter_wifi_station_state();

  /**
  *   \brief Perform any necessary configurations and enter deep sleep.
  *   \return status Indicates exit status (any status return is bad here).
  *
  *   This method may undergo changes depending on microcontroller architecture
  *   and board functionality; for example, ESP32 Thing requires both slow and
  *   fast memory to be disabled to achieve optimal performance.
  *
  *   Currently, we allow 3 things to wake the board: the RTC alarm on pin 39,
  *   button press on pin 32, and button press on pin 25. These are each
  *   handled differently on wakeup (because each wakeup implies different
  *   desired behavior).
  *
  *
  */
  uint8_t enter_sleep();

private:
};
