#include "main.h"

void handle_wakeup(RTC_container clock){
  esp_deep_sleep_wakeup_cause_t reason;
  reason = esp_deep_sleep_get_wakeup_cause();
  switch(reason){
    case 1  :
      Serial.println("Wakeup caused by external signal using RTC_IO (Interrupt from RTC)");
      //clock.print_date();
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
      int8_t clock_status;
      clock_status = clock.check_datetime();
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
  delay(1000); // wait for console opening
  RTC_container clock;
  handle_wakeup(clock); //do whatever it is we do when we wake up
  clock.setup();

  //NVS_container setup
  NVS_container nvs;
  nvs.setup();
  long clock_data =clock.rtc.now().secondstime();
  memcpy(nvs.data.time_buf, &clock_data, sizeof(clock_data));

  // TemperatureSensor setup and read
  TemperatureSensor ts;
  int8_t status;
  uint8_t len;
  uint8_t* data = (uint8_t*)malloc(4 * sizeof(uint8_t));
  status = ts.setup();
  len = ts.read(data);
  Serial.printf("Temperature value: %f\n", bytes_to_float(data));
  memcpy(nvs.data.temp_buf,data, sizeof(data));
  free(data);


  // SonicRangeSensor setup and read
  // TODO: utils.h function for long->byte[]; then use here.
  SonicRangeSensor srs;
  data = (uint8_t*)malloc(1 * sizeof(long));
  status = srs.setup();
  len = srs.read(data);
  Serial.printf("Sonic Range value: %u\n", *data); // number issues
  free(data);

  nvs.write_data();
  nvs.zero_data();
  nvs.read_data(1);
  Serial.printf("First recorded value: %f\n", bytes_to_float(nvs.data.temp_buf));
  if(nvs.get_counter() >= MAX_NVS_COUNTER){
    // TODO open up SD cards and move data over.
    // NOTE we will still use clear() at the end.
    Serial.printf("NVS data cleared.\n");
    nvs.clear();
  }
  nvs.close();

  enter_sleep();
}

void loop () {
}
