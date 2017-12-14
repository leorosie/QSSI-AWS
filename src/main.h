#define CONFIG_MBEDTLS_HARDWARE_MPI 0
#define CONFIG_MBEDTLS_DEBUG 1
#define CONFIG_MBEDTLS_MPI_USE_INTERRUPT 0

#include "pins.h"
#include <Wire.h>

#include "PowerState.h"
#include "utils.h"
#include "TemperatureSensor.h"
#include "SonicRangeSensor.h"
#include "PyranometerSensor.h"
#include "RTC_container.h"
#include "NVS_container.h"
#include "SD_container.h"
#include "Wifi_container.h"

extern const int SD_CARD_1_SS;
extern const int SD_CARD_2_SS;

/**
*  \brief Handle any wakeup event (including power on).
*  \param state A PowerState object ptr which switchs power rails and
*         manages deep sleep.
*  \param clock An RTC_container object ptr, which contains methods that are
*         useful for timed events.
*  \param nvs A NVS_container object ptr which wraps the chip's non-volatile
*         storage for other components to easily access.
*  \see RTC_container::print_date()
*  \see PowerState::enter_sleep()
*  \return void
*
*  Wakeup is a complex topic in ESP32 and I can't get into all the details
*  in a simple comment. See the above sections of code for more information
*  and the user manual for details.
*/
void handle_wakeup(PowerState* state, RTC_container* clock, NVS_container* nvs);

/**
*  \brief Arduino-required routine runs when powered on.
*
*  This Arduino-required function does some preliminary setup then calls our
*  handle_wakeup routine to figure out what happens next. It is the owner
*  of all of our semi-persistent objects.
*/
void setup ();

/**
* \brief Start up our wifi code to share data.
*
* This optional mode will be entered when the user holds the wifi button to wake
* the chip. It's quite likely that this code will not actually be used. It also
* handles the transfer of data from NVS to the wifi module.
*/
void wifi_mode(PowerState* state, RTC_container* clock, NVS_container* nvs);

/** Arduino-required routine that loops forever after setup.
*
*  We shouldn't ever reach this function unless something goes drastically
*  wrong with our code; we should wake up in setup, do stuff, and go back
*  to sleep all without ever touching this loop.
*/
void loop ();

/**
*  \brief Default actions on RTC wakeup.
*  \param state A PowerState object ptr which switchs power rails and
*         manages deep sleep.
*  \param clock An RTC_container object ptr, which contains methods that are
*         useful for timed events.
*  \param nvs A NVS_container object ptr which wraps the chip's non-volatile
*         storage for other components to easily access.
*  For now, this only calls a normal read cycle on our sensors but it could
*  be expanded in the future to include other functionality.
*/
void do_wake_operations(PowerState* state, RTC_container* clock, NVS_container* nvs);

/**
*  \brief Actions for button wakeup.
*  \param state A PowerState object ptr which switchs power rails and
*         manages deep sleep.
*  \param clock An RTC_container object ptr, which contains methods that are
*         useful for timed events.
*  \param nvs A NVS_container object ptr which wraps the chip's non-volatile
*         storage for other components to easily access.
*
*  The board can be awakened by two buttons: a wifi button and a sd card button.
*  This function figures out which one was pressed and starts the appropriate
*  routines.
*/
void do_button_operations(PowerState* state, RTC_container* clock, NVS_container* nvs);

/**
*  \brief Write out the NVS to SD cards.
*  \param state A PowerState object ptr which switchs power rails and
*         manages deep sleep.
*  \param nvs A NVS_container object ptr which wraps the chip's non-volatile
*         storage for other components to easily access.
*  \param card_num Identifier for the SD cards on the board.
*
*  In order to handle the erratic behavior of our SD cards, we need to do
*  considerable error checking and have contingencies in application logic.
*  This function takes care of much of that.
*/
int write_out(PowerState* state, NVS_container* nvs, int card_num);

/**
*  \brief Read from sensors and store data in NVS.
*  \param state A PowerState object ptr which switchs power rails and
*         manages deep sleep.
*  \param clock An RTC_container object ptr, which contains methods that are
*         useful for timed events.
*  \param nvs A NVS_container object ptr which wraps the chip's non-volatile
*         storage for other components to easily access.
*
*  This manages a lot of little objects but it's quite straightforward. It
*  sets up a sensor, reads from it, and writes it into NVS. At the end, it
*  checks to see if it needs to write_out() to SD cards.
*/
int read_sensors(PowerState* state, RTC_container* clock, NVS_container* nvs);
