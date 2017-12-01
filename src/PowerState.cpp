#include "PowerState.h"

PowerState::PowerState(){
  //sleep wakeup pin
  pinMode(WAKE_PIN, INPUT);
  //sensor inputs
  pinMode(SONIC_RANGER_BUS, INPUT);
  pinMode(ONE_WIRE_BUS, INPUT);
  pinMode(PYRO_ADC_IN_1, INPUT);
  pinMode(PYRO_ADC_IN_2, INPUT);
  //power selectors
  pinMode(SENSOR_POWER_BUS, OUTPUT);
  pinMode(SD_CARD_1_POWER_BUS, OUTPUT);
  pinMode(SD_CARD_2_POWER_BUS, OUTPUT);
  pinMode(SD_CARD_1_SS, OUTPUT);
  pinMode(SD_CARD_2_SS, OUTPUT);
  //misc
  pinMode(FLUSH_NVS_SWITCH, INPUT);
  pinMode(FLUSH_NVS_LED, OUTPUT);
  pinMode(WIFI_STATION_SWITCH, INPUT);
  //turn on/off anything for basic operation
  this->enter_basic_state();
}

PowerState::~PowerState(){
  delete this;
}

uint8_t PowerState::enter_basic_state(){
  uint8_t status = 0;
  digitalWrite(SENSOR_POWER_BUS, LOW);
  digitalWrite(SD_CARD_1_POWER_BUS, LOW);
  digitalWrite(SD_CARD_2_POWER_BUS, LOW);
  digitalWrite(SD_CARD_1_SS, LOW);
  digitalWrite(SD_CARD_2_SS, LOW);
  digitalWrite(PYRANOMETER_CS_PIN, HIGH);
  digitalWrite(FLUSH_NVS_LED, LOW);
  delay(100);
  return(status);
}

uint8_t PowerState::enter_sensor_state(){
  uint8_t status = 0;
  this->enter_basic_state();
  digitalWrite(SENSOR_POWER_BUS, HIGH);
  return(status);
}

uint8_t PowerState::enter_SD_card_write_state(uint8_t number){
  uint8_t status = 0;
  this->enter_basic_state();
  if(number == 1){
    Serial.println("entering SD 1 state");
    digitalWrite(SD_CARD_1_POWER_BUS, HIGH);
    digitalWrite(SD_CARD_1_SS, LOW);
  } else if (number == 2){
    Serial.println("entering SD 2 state");
    digitalWrite(SD_CARD_2_POWER_BUS, HIGH);
    digitalWrite(SD_CARD_2_SS, LOW);
  } else {
    status = -1;
  }
  return(status);
}

uint8_t PowerState::enter_wifi_station_state(){
  uint8_t status = 0;
  this->enter_basic_state();
  //TODO: switch anything we need for wifi station power mode
  return(status);
}

uint8_t PowerState::enter_sleep(){
  uint8_t status = -1; //shouldn't ever return, so if it does there's a problem
  this->enter_basic_state();
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_deep_sleep_enable_ext0_wakeup(WAKE_PIN, 0);
  // NOTE: we need pullup resistors on these GPIO pins; else auto-wake!
  //esp_deep_sleep_enable_ext0_wakeup(FLUSH_NVS_SWITCH, 0);
  //esp_deep_sleep_enable_ext0_wakeup(WIFI_STATION_SWITCH, 0);
  Serial.println("Entering deep sleep...");
  esp_deep_sleep_start();
  return(status);
}
