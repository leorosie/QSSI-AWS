#include "main.h"

void handle_wakeup(RTC_container clock){
  esp_deep_sleep_wakeup_cause_t reason;
  reason = esp_deep_sleep_get_wakeup_cause();
  switch(reason){
    case 1  :
      Serial.println("Wakeup caused by external signal using RTC_IO (Interrupt from RTC)");
      clock.print_date();
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

void enter_sleep(){
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_deep_sleep_enable_ext0_wakeup(WAKE_PIN, 0);
  Serial.println("Entering deep sleep...");
  esp_deep_sleep_start();
  Serial.println("If printed, system is not asleep.");
}

void setup () {
  Serial.begin(115200);
  Wire.begin(); // this prevents some time weirdness from rtc
  RTC_container clock;
  clock.setup();
  delay(1000); // wait for console opening
  handle_wakeup(clock); //do whatever it is we do when we wake up

  // TemperatureSensor setup and read
  TemperatureSensor ts;
  int8_t status;
  uint8_t* data;
  status = ts.setup();
  data = ts.read();
  //Serial.println("Temperature: %u", *data);

  // SonicRangeSensor setup and read
  SonicRangeSensor srs;
  status = srs.setup();
  data = srs.read();

  enter_sleep();
}

void loop () {
}
