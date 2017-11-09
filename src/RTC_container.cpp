#include "RTC_container.h"

int8_t RTC_container::setup(){
  int8_t status = 0;
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    status = -1;
    return(status);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power; resetting to compile time.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  //clear alarms before we initialize
  rtc.armAlarm(1, false);
  rtc.clearAlarm(1);
  rtc.alarmInterrupt(1, false);
  rtc.armAlarm(2, false);
  rtc.clearAlarm(2);
  rtc.alarmInterrupt(2, false);

  //set mode; set alarm; arm interrupt
  //TODO: change to set next alarm on interval from current time
  rtc.writeSqwPinMode(DS3231_OFF);
  //rtc.setAlarm(ALM1_MATCH_SECONDS, 0, 0, 0, 0);
  rtc.setAlarm(ALM1_EVERY_SECOND, 0, 0, 0, 0);
  rtc.alarmInterrupt(1, true);

  return(status);
}

void RTC_container::print_date(){
    DateTime now = rtc.now();
    Serial.println();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    Serial.println();
}

// TODO fill out this method
int8_t RTC_container::set_next_alarm(int8_t seconds){
  int8_t status = 0;
  return(status);
}
