#include <Arduino.h>
#include <Wire.h>
#include "RTClibExtended.h"
#include "esp_system.h"
#include "esp_deep_sleep.h"

#include "TemperatureSensor.h"

/*
TODO: write a function that takes an interval value and current time to make
an alarm for (time + interval) to get around the limitations of the chip
*/

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const int snow=12;
long sensor, mm, inches;

void read_sensor() {
  sensor=pulseIn(snow,HIGH);
  mm=(sensor-498.0);
  inches=mm/25.4;
}


void print_date(){
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

void handle_wakeup(){
  esp_deep_sleep_wakeup_cause_t reason;
  reason = esp_deep_sleep_get_wakeup_cause();
  switch(reason){
    case 1  :
      Serial.println("Wakeup caused by external signal using RTC_IO (Interrupt from RTC)");
      print_date();
      //read_sensor();
      break;
    case 2  :
      Serial.println("Wakeup caused by external signal using RTC_CNTL");
      break;
    case 3  :
      Serial.println("Wakeup caused by timer");
      break;
    case 4  :
      Serial.println("Wakeup caused by touchpad");
      break;
    case 5  :
      Serial.println("Wakeup caused by ULP program");
      break;
    default :
      Serial.println("Wakeup was not caused by deep sleep");
      break;
    }
}

void setup () {
  Serial.begin(115200);
  pinMode(snow, INPUT);
  Wire.begin();// this prevents some time weirdness from rtc
  delay(1000); // wait for console opening
  handle_wakeup(); //do whatever it is we do when we wake up
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Temperature sensor setup and read
  TemperatureSensor ts;
  ts.setup();
  ts.read();

  //clear alarms before we initialize
  rtc.armAlarm(1, false);
  rtc.clearAlarm(1);
  rtc.alarmInterrupt(1, false);
  rtc.armAlarm(2, false);
  rtc.clearAlarm(2);
  rtc.alarmInterrupt(2, false);

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
  //esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_deep_sleep_enable_ext0_wakeup(GPIO_NUM_39, 0);
  Serial.println("Entering deep sleep...");
  esp_deep_sleep_start();
  Serial.println("If printed, system is not asleep.");
}

void loop () {
}
