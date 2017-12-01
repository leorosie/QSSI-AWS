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

extern const int SD_CARD_1_SS
extern const int SD_CARD_2_SS

/** Handle any wakeup event (including power on).
*   \param clock an RTC_container object, which contains methods that are
*          useful for timed events.
*   \see RTC_container::print_date()
*   \return void
*/
void handle_wakeup(RTC_container);

/** Arduino-required routine runs when powered on.
*
*   Most of our logic will need to be in here since waking from ESP32 sleep is
*   treated as power on; we will use esp_deep_sleep_wakeup_cause_t to figure
*   out what woke up the chip and what should be done about it.
*/
void setup ();

/** Arduino-required routine that loops forever after setup.
*
*   We shouldn't ever reach this function unless something goes drastically
*   wrong with our code; we should wake up in setup, do stuff, and go back
*   to sleep all without ever touching this loop.
*/
void loop ();
