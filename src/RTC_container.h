#pragma once

#include "pins.h"
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
  *   \brief Print out the current time.
  *
  */
  void print_date();

  /**
  *   \brief Prepare the RTC for operation.
  *
  *   \return status an int (0 -> success, -1 -> error)
  */
  int8_t setup();

  /**
  *   \brief Set the next alarm to wake up the chip.
  *
  *   \param seconds a count of seconds from current time at which the
  *          next alarm should be set.
  *   \return status an int (0 -> success, -1 -> error)
  *
  *   This is here to get us around the limitations of the
  *   RTC which can only take one second intervals or some
  *   future time to set an alarm.
  */
  int8_t set_next_alarm(int8_t seconds);

private:

  /**
  *  \var RTC_DS3231 rtc
  *
  *  \brief A real-time clock object.
  *
  *  An instance of a RTC_DS3231, capable of sending both
  *       square waves and interrupts to a pin on the board.
  */
  RTC_DS3231 rtc;

  /**
  *   \var char[][] daysOfTheWeek
  *   \brief A list of week days.
  *
  *   This is used by some printouts but not exactly critical for
  *   field operations.
  */
  char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
};
