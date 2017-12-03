#include "main.h"

void handle_wakeup(RTC_container clock){
  PowerState state;
  int status = 1;
  esp_deep_sleep_wakeup_cause_t reason;
  reason = esp_deep_sleep_get_wakeup_cause();
  switch(reason){
    case 1  :
      Serial.println("Wakeup caused by external signal using RTC_IO (Interrupt from RTC)");
      do_wake_operations(clock);
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
      do_restart_operations(clock);
      break;
    }
}

void do_restart_operations(RTC_container clock){
  PowerState state;
  int status;
  Serial.println("first read...");
  status = read_sensors(clock);
  Serial.println("now going to write out...");
  status = -1;
  Serial.println("now going to sleep...");
  state.enter_sleep();
}

 void do_wake_operations(RTC_container clock){
  PowerState state;
  int status;
  status = read_sensors(clock);
  status = -1;
  Serial.println("now going to sleep...");
  state.enter_sleep();
 }

void setup () {
  Serial.begin(115200);
  delay(100); // wait for console opening
  Serial.printf("in setup\n");
  RTC_container clock;
  handle_wakeup(clock); //do whatever it is we do when we wake up
}

int write_out(NVS_container* nvs){
  PowerState state;
  state.enter_basic_state();
  nvs->zero_data();
  int8_t sd_state = 0;
  SD_container sd;
  sd = SD_container();
  state.enter_SD_card_write_state(2);
  delay(100);
  Serial.printf("writing\n");
  sd_state = sd.setup("/test.txt", sizeof("/test.txt"), SD_CARD_2_SS);
  Serial.printf("SD state on setup: %d\n", sd_state);
  if(sd_state == -9){
    Serial.printf("SD write returned error code: %d\n", sd_state);
    sd.close();
    nvs->set_fails(1);
    //nvs->close();
    return(-1);
  }
  int i;
  for(i = 0; i < nvs->get_counter(); ++i){
    sd.make_line(nvs,i);
  }
  sd.close();

  // TODO open up SD cards and move data over.
  // NOTE we will still use clear() at the end.
  nvs->clear();
  //nvs->close();
  //state.enter_sleep();
  return(0);
}

int read_sensors(RTC_container clock){
  PowerState state;
  Wire.begin();
  //RTC_container clock;
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

  //keep track of whether we did this
  uint8_t handled_fails = 0;
  //SD card check (did we fail last time?)
  uint16_t fails = nvs.get_fails();
  if (fails > 0){
    Serial.printf("last SD write failed; trying again now!\n");
    status = write_out(&nvs);
    handled_fails = 1;
    if (status == 0){
      Serial.printf("New write out was successful!\n");
      nvs.set_fails(0);
    } else {
      Serial.printf("New write out failed. damn.\n");
    }
  }

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
  if(nvs.get_counter() >= MAX_NVS_COUNTER){
    write_out(&nvs);
    //if(handled_fails == 1){
    //  nvs.clear();
    //}
  }
  nvs.close();
  Serial.printf("done in read.\n");
  return(0);
}

void loop () {

}
