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

void setup () {
  PowerState state;
  Serial.begin(115200);
  Wire.begin();
  delay(1000); // wait for console opening
  RTC_container clock;
  handle_wakeup(clock); //do whatever it is we do when we wake up
  clock.setup();
  int8_t state_status;
  state_status = state.enter_sensor_state();

  //define some variables for use in this function
  int8_t status;
  uint8_t len;
  uint8_t data[64];

  //NVS_container setup
  NVS_container nvs;
  nvs.setup();
  long clock_data =clock.rtc.now().secondstime();
  memcpy(nvs.data.time_buf, &clock_data, sizeof(clock_data));


  // TemperatureSensor setup and read
  TemperatureSensor ts;
  status = ts.setup();
  len = ts.read(data);
  Serial.printf("Temperature value: %f\n", bytes_to_float(data));
  memcpy(nvs.data.temp_buf, &data, len);
  memset(&data, 0, sizeof(data));

  // SonicRangeSensor setup and read
  SonicRangeSensor srs;
  status = srs.setup();
  len = srs.read(data);
  Serial.printf("Sonic Range value: %ld\n", *data); // number issues
  memcpy(nvs.data.temp_buf, &data, len);
  memset(&data, 0, sizeof(data));

  PyranometerSensor ps;
  status = ps.setup();
  len = ps.read(data);
  Serial.printf("Pyranometer value: %u\n", bytes_to_float(data));
  memcpy(nvs.data.temp_buf, &data, len);
  memset(&data, 0, sizeof(data));

  nvs.write_data();
  nvs.zero_data();
  nvs.read_data(1);
  Serial.printf("First recorded value: %f\n", bytes_to_float(nvs.data.temp_buf));
  //if(nvs.get_counter() >= MAX_NVS_COUNTER){
    //SD_container setup
    SD_container sd;
    state.enter_SD_card_write_state(1);
    //state.enter_SD_card_write_state(2);
    sd.setup("/test.txt", sizeof("/test.txt"), 4);

    sd.make_line(nvs,2);
    sd.close();


    // TODO open up SD cards and move data over.
    // NOTE we will still use clear() at the end.
    Serial.printf("NVS data cleared.\n");
    nvs.clear();
//  }
  nvs.close();

  state.enter_sleep();
}

void loop () {

}
