#include "main.h"

void handle_wakeup(PowerState* state, RTC_container* clock, NVS_container* nvs){
  int status = 1;
  esp_deep_sleep_wakeup_cause_t reason;
  reason = esp_deep_sleep_get_wakeup_cause();
  switch(reason){
    case 1  :
      Serial.println("Wakeup caused by external signal using RTC_IO (Interrupt from RTC)");
      Wire.begin();
      clock->setup();
      do_wake_operations(state, clock, nvs);
      break;
    case 2  :
      Serial.println("Wakeup caused by external signal using RTC_CNTL");
      Wire.begin();
      clock->setup();
      do_button_operations(state, clock, nvs);
      break;
    default :
      Serial.println("Wakeup was not caused by deep sleep (probably powering on)");
      Wire.begin();
      int8_t clock_status = clock->check_datetime();
      clock->setup();
      do_wake_operations(state, clock, nvs);
      break;
    }
}

void do_wake_operations(PowerState* state, RTC_container* clock, NVS_container* nvs){
  int status = read_sensors(state, clock, nvs);
  state->enter_sleep();
}

void do_button_operations(PowerState* state, RTC_container* clock, NVS_container* nvs ){
  if(digitalRead(WIFI_STATION_SWITCH) == HIGH){
    wifi_mode(state, clock, nvs);
    while(digitalRead(WIFI_STATION_SWITCH) == HIGH); //let go of the button
  } else if (digitalRead(FLUSH_NVS_SWITCH) == HIGH) {
    write_out(state, nvs, 1);
    nvs->close();
    while(digitalRead(FLUSH_NVS_SWITCH) == HIGH); //LET GO OF THE GD BUTTON
  } else {
    Serial.println("Button wasn't held long enough to determine command.");
  }
  state->enter_sleep();
}

void setup () {
  Serial.begin(115200);
  delay(100); // wait for console opening
  PowerState state;
  RTC_container clock;
  NVS_container nvs;
  uint8_t nvs_status = nvs.setup();
  handle_wakeup(&state, &clock, &nvs); //do whatever it is we do when we wake up
}

int write_out(PowerState* state, NVS_container* nvs, int card_num){
  nvs->zero_data();
  int8_t sd_state = 0;
  SD_container sd;
  sd = SD_container();
  if(card_num == 1){
    state->enter_SD_card_write_state(1);
    delay(100);
    sd_state = sd.setup("/test.txt", sizeof("/test.txt"), SD_CARD_1_SS);
  } else if (card_num == 2) {
    state->enter_SD_card_write_state(2);
    delay(100);
    sd_state = sd.setup("/test.txt", sizeof("/test.txt"), SD_CARD_2_SS);
  }
  if(sd_state == -9){
    sd.close();
    if(card_num == 1 && nvs->get_fails() == 2){
      nvs->set_fails(3);
    } else if(card_num == 1 && nvs->get_fails() == 1){
      nvs->set_fails(1);
    } else if(card_num == 2 && nvs->get_fails() == 1){
      nvs->set_fails(3);
    } else if(card_num == 2 && nvs->get_fails() == 2){
      nvs->set_fails(2);
    } else {
      Serial.println("Card error count is off; what happened??");
    }
    return(-1);
  }
  int i;
  for(i = 0; i < nvs->get_counter(); ++i){
    sd.make_line(nvs,i);
  }
  sd.close();
  if((nvs->get_fails() == 0) && (card_num == 1)){ //TODO change to 2 when fixed
    nvs->clear();
  }
  state->enter_basic_state();
  return(0);
}

int read_sensors(PowerState* state, RTC_container* clock, NVS_container* nvs){
  int8_t state_status;
  state_status = state->enter_sensor_state();

  //define some variables for use in this function
  int8_t status;
  uint8_t len;
  uint8_t data[64];

  //SD card check (did we fail last time we tried to write out?)
  uint16_t fails = nvs->get_fails();
  uint8_t card1_status;
  uint8_t card2_status;
  if (fails > 0){
    Serial.printf("last SD write failed; trying again now!\n");
    card1_status = write_out(state,nvs,1);
    //card2_status = write_out(state,nvs,2);
    status = card1_status + card2_status;
    if (status == 0){
      Serial.printf("New write out was successful!\n");
      nvs->set_fails(0);
    } else {
      Serial.printf("New write out failed. damn.\n");
    }
  }

  long clock_data = clock->rtc.now().secondstime();
  memcpy(nvs->data.time_buf, &clock_data, sizeof(clock_data));

  // TemperatureSensor setup and read
  TemperatureSensor ts;
  status = ts.setup();
  len = ts.read(data);
  Serial.printf("Temperature value: %f\n", bytes_to_float(data));
  memcpy(nvs->data.temp_buf, &data, len);
  memset(&data, 0, sizeof(data));

  // SonicRangeSensor setup and read
  SonicRangeSensor srs;
  status = srs.setup();
  len = srs.read(data);
  Serial.printf("Sonic Range value: %ld\n", bytes_to_long(data)); // number issues
  memcpy(nvs->data.snow_buf, &data, len);
  memset(&data, 0, sizeof(data));

  // PyranometerSensor setup and read
  PyranometerSensor ps;
  status = ps.setup();
  len = ps.read(data);
  Serial.printf("Pyranometer value: %u\n", bytes_to_float(data));
  memcpy(nvs->data.pyro_buf, &data, len);
  memset(&data, 0, sizeof(data));

  nvs->write_data();
  if(nvs->get_counter() >= MAX_NVS_COUNTER){
    write_out(state,nvs,1);
    //write_out(state,nvs,2);
  }
  nvs->close();
  return(0);
}

void wifi_mode(PowerState* state, RTC_container* clock, NVS_container* nvs){
  state->enter_wifi_station_state();
  nvs->read_data(nvs->get_counter()-1);
  Wifi_container wifi;
  memcpy(wifi.data.time_buf, nvs->data.time_buf, sizeof(nvs->data.time_buf));
  memcpy(wifi.data.temp_buf, nvs->data.temp_buf, sizeof(nvs->data.temp_buf));
  memcpy(wifi.data.snow_buf, nvs->data.snow_buf, sizeof(nvs->data.snow_buf));
  memcpy(wifi.data.pyro_buf, nvs->data.pyro_buf, sizeof(nvs->data.pyro_buf));
  nvs->close();
  wifi.setup();
  wifi.host();
  wifi.close();
  clock->setup();
}

void loop () {

}
