#pragma once

#include "pins.h"
#include <Wire.h>
#include "RTClibExtended.h"

/**
 * \class RTC_container
 * \brief Wraps the RTC_DS3231 object for ease of use.
 *
 * As written, the RTC_DS3231 lacks some features we would like for
 * our project, such as a dedicated timestamp method and a simple
 * repeating alarm system. In addition, we want to simplify the
 * setup procedure into a smaller call.
 */
class RTC_container {
public:

  /**
  *   \brief Update RTC date/time if needed.
  *
  *   \return status An int (0 -> no change, 1 -> change, other -> error)
  *
  *   This check will only take place when the system isn't woken up
  *   from deep sleep (e.g. it is first powered on).
  *   TODO are there other cases we need to check?
  */
  int8_t check_datetime();

  /**
  *   \brief Print out the contents of a DateTime (human readable).
  *   \param t A DateTime object.
  *
  */
  void print_date(DateTime t);

  /**
  *   \brief Prepare the RTC for operation.
  *
  *   \return status An int (0 -> success, -1 -> error)
  */
  int8_t setup();

  /**
  *   \brief Set the next alarm to wake up the chip.
  *
  *   \param seconds A count of seconds from current time at which the
  *          next alarm should be set.
  *   \return status An int (0 -> success, -1 -> error)
  *
  *   This is here to get us around the limitations of the
  *   RTC which can only take one second intervals or some
  *   future time to set an alarm.
  */
  int8_t set_next_alarm(int32_t seconds, int8_t alarm_num);

  RTC_DS3231 rtc;
private:

  /**
  *  \var RTC_DS3231 rtc
  *
  *  \brief A real-time clock object.
  *
  *  An instance of a RTC_DS3231, capable of sending both
  *       square waves and interrupts to a pin on the board.
  */
  //RTC_DS3231 rtc;

  /**
  *   \var char[][] daysOfTheWeek
  *   \brief A list of week days.
  *
  *   This is used by some printouts but not exactly critical for
  *   field operations.
  */
  char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  /**
  *   \var sleep_time
  *   \brief Sleep time in seconds between sensor readings
  *
  *   The RTC sends a signal to wake the chip so that it can take readings
  *   from the sensors. This field sets the length of time between signals.
  *
  */
  int32_t sleep_time;
};
