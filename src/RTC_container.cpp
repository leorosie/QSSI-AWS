#include "RTC_container.h"

int8_t RTC_container::check_datetime(){
  int8_t status;
  Serial.println("Checking RTC time...");
  //TODO this needs to rtc.begin() first
  if (this->rtc.lostPower()) {
    Serial.println("RTC lost power; resetting to compile time.");
    this->rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    status = 1;
  } else {
    Serial.println("RTC time is OK!");
    status = 0;
  }
  return(status);
}

int8_t RTC_container::setup(){
  Wire.begin();
  int8_t status = 0;
  this->sleep_time = 65; // TODO set for field interval (15m) before deploying.
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    status = -1;
    return(status);
  }
  //clear alarms before we initialize
  rtc.armAlarm(1, false);
  rtc.clearAlarm(1);
  rtc.alarmInterrupt(1, false);
  rtc.armAlarm(2, false);
  rtc.clearAlarm(2);
  rtc.alarmInterrupt(2, false);
  //set mode; set alarm; arm interrupt
  rtc.writeSqwPinMode(DS3231_OFF);
  this->set_next_alarm(this->sleep_time, 1);
  rtc.alarmInterrupt(1, true);
  return(status);
}

void RTC_container::print_date(DateTime t){
    Serial.println();
    Serial.print(t.year(), DEC);
    Serial.print('/');
    Serial.print(t.month(), DEC);
    Serial.print('/');
    Serial.print(t.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[t.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(t.hour(), DEC);
    Serial.print(':');
    Serial.print(t.minute(), DEC);
    Serial.print(':');
    Serial.print(t.second(), DEC);
    Serial.println();
    Serial.println();
}

//TODO clean out print statements before deploying.
int8_t RTC_container::set_next_alarm(int32_t seconds, int8_t alarm_num){
  int8_t status = 0;
  DateTime now = rtc.now();
  Serial.println("Current time: ");
  this->print_date(now);
  Serial.println("Next wake time: ");
  DateTime next_alarm = now + seconds;
  this->print_date(next_alarm);
  if (alarm_num == 1) {
    rtc.setAlarm(ALM1_MATCH_HOURS, next_alarm.second(), next_alarm.minute(),
      next_alarm.hour(), next_alarm.day());
  } else if (alarm_num == 2) { // seconds is always 0 on alarm 2!
    rtc.setAlarm(ALM2_MATCH_HOURS, 0, next_alarm.minute(),
      next_alarm.hour(), next_alarm.day());
  }
  return(status);
}
