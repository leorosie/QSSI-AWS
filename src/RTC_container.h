#pragma once
#include "pins.h"
#include "RTClibExtended.h"

class RTC_container {
public:

  /** Print out the current time.
  *
  */
  void print_date();

  /** Prepare the RTC for operation.
  *
  */
  int8_t setup();

  /** Set the next alarm to wake up the chip.
  *
  *   this is here to get us around the limitations of the
  *   RTC which can only take one second intervals or some
  *   future time to set an alarm.
  */
/*
TODO: write a function that takes an interval value and current time to make
an alarm for (time + interval) to get around the limitations of the chip
*/
  int8_t set_next_alarm(int8_t seconds);

private:
  RTC_DS3231 rtc;
  char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
};
