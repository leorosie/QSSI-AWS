#include "RTC_container.h"

int8_t RTC_container::setup(){
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  Ds3231SqwPinMode mode = rtc.readSqwPinMode();
  Serial.printf("Current i2c device mode: %x\n", (byte)mode);
  Serial.println("Now writing mode to i2c device...");
  rtc.writeSqwPinMode(DS3231_OFF);
  //NOTE signature void setAlarm(Ds3231_ALARM_TYPES_t alarmType, byte seconds,
  //                             byte minutes, byte hours, byte daydate);
  rtc.setAlarm(ALM1_MATCH_SECONDS, 0, 0, 0, 0);
  //rtc.setAlarm(ALM1_EVERY_SECOND, 0, 0, 0, 0);
  rtc.alarmInterrupt(1, true);

  mode = rtc.readSqwPinMode();
  Serial.printf("Current i2c device mode: %x\n", (byte)mode);
  }

  //clear alarms before we initialize
  rtc.armAlarm(1, false);
  rtc.clearAlarm(1);
  rtc.alarmInterrupt(1, false);
  rtc.armAlarm(2, false);
  rtc.clearAlarm(2);
  rtc.alarmInterrupt(2, false);

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

// TODO fill out this methos
int8_t RTC_container::set_next_alarm(int8_t seconds){
  int8_t status = 0;
  return(status);
}
