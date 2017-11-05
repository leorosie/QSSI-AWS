#include "RTC_container.h"

int8_t RTC_container::check_datetime(){
  int8_t status;
  Serial.println("Checking RTC time...");
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
  int32_t seconds = 120;
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
  //TODO: change to set next alarm on interval from current time
  rtc.writeSqwPinMode(DS3231_OFF);
  //rtc.setAlarm(ALM1_MATCH_SECONDS, 0, 0, 0, 0);

  printf("%d\n", seconds );
  Serial.println("Current time: ");
  this->print_date();
  Serial.println("Next wake time: ");
  this->set_next_alarm(seconds, 1);
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
int8_t RTC_container::set_next_alarm(int32_t seconds, int8_t alarm_num){
  int8_t status = 0;
  DateTime now = rtc.now();
  long now_seconds = now.secondstime();
  //Serial.printf("%ld  %d\n", (long)seconds, seconds);
  Serial.printf("%ld\n", now_seconds );
  now_seconds += (long) seconds;
  Serial.printf("%ld\n", now_seconds );
  //DateTime next_alarm = DateTime(now_seconds);
  DateTime next_alarm = now + seconds;
    Serial.println();
    Serial.print(next_alarm.year(), DEC);
    Serial.print('/');
    Serial.print(next_alarm.month(), DEC);
    Serial.print('/');
    Serial.print(next_alarm.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[next_alarm.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(next_alarm.hour(), DEC);
    Serial.print(':');
    Serial.print(next_alarm.minute(), DEC);
    Serial.print(':');
    Serial.print(next_alarm.second(), DEC);
    Serial.println();
    Serial.println();
  if (alarm_num == 1) {
    rtc.setAlarm(ALM1_MATCH_HOURS, next_alarm.second(), next_alarm.minute(),
      next_alarm.hour(), next_alarm.day());
  } else if (alarm_num == 2) { // seconds is always 0 on alarm 2!
    rtc.setAlarm(ALM2_MATCH_HOURS, 0, next_alarm.minute(),
      next_alarm.hour(), next_alarm.day());
  }
  return(status);
}
