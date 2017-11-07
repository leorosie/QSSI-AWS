#include "NVS_container.h"

uint8_t NVS_container::setup(){
  uint8_t status;
  this->accessor.begin("AWS_data", false);
  this->zero_data();
  uint8_t sub_status = this->get_counter();
  if(sub_status != 0){
    Serial.println("no existing counter; making it now");
    this->accessor.putShort("counter", 1);
  }
  return(status);
}

uint8_t NVS_container::close(){
  uint8_t status;
  this->set_counter();
  this->accessor.end();
  return(status);
}

uint8_t NVS_container::read_data(uint16_t index){
  uint8_t status;
  this->zero_data();
  char key_buf[16]; //max size of key==16 TODO define constant in .h?
  // timestamp
  char key_str[] = "time_%hd";
  sprintf(key_buf, key_str, index);
  this->accessor.getBytes(key_buf, this->data.time_buf, 64);
  // temperature
  strcpy(key_str, "temp_%hd");
  sprintf(key_buf, key_str, index);
  this->accessor.getBytes(key_buf, this->data.temp_buf, 64);
  // snow depth
  strcpy(key_str, "snow_%hd");
  sprintf(key_buf, key_str, index);
  this->accessor.getBytes(key_buf, this->data.snow_buf, 64);
  // pyranometer
  strcpy(key_str, "pyro_%hd");
  sprintf(key_buf, key_str, index);
  this->accessor.getBytes(key_buf, this->data.pyro_buf, 64);
  return(status);
}

uint8_t NVS_container::write_data(){
  uint8_t status;
  char key_buf[16]; //max size of key==16 TODO define constant in .h?
  // timestamp
  char key_str[] = "time_%hd";
  sprintf(key_buf, key_str, this->counter);
  this->accessor.putBytes(key_buf,this->data.time_buf,sizeof(this->data.time_buf));
  // temperature
  strcpy(key_str, "temp_%hd");
  sprintf(key_buf, key_str, this->counter);
  this->accessor.putBytes(key_buf,this->data.temp_buf,sizeof(this->data.time_buf));
  // snow depth
  strcpy(key_str, "snow_%hd");
  sprintf(key_buf, key_str, this->counter);
  this->accessor.putBytes(key_buf,this->data.snow_buf,sizeof(this->data.snow_buf));
  // pyranometer
  strcpy(key_str, "pyro_%hd");
  sprintf(key_buf, key_str, this->counter);
  this->accessor.putBytes(key_buf,this->data.pyro_buf,sizeof(this->data.pyro_buf));
  // increment counter since we just wrote in another entry
  ++this->counter;
  return(status);
}

uint8_t NVS_container::zero_data(){
  uint8_t status;
  memset(this->data.time_buf, 0, sizeof(this->data.time_buf));
  memset(this->data.temp_buf, 0, sizeof(this->data.temp_buf));
  memset(this->data.snow_buf, 0, sizeof(this->data.snow_buf));
  memset(this->data.pyro_buf, 0, sizeof(this->data.pyro_buf));
  return(status);
}

uint8_t NVS_container::get_counter(){
  uint8_t status = 0;
  this->counter = this->accessor.getShort("counter",0); //0 -> not found
  if(this->counter == 0){
    status = -1;
  }
  return(status);
}

uint8_t NVS_container::set_counter(){
  uint8_t status;
  Serial.printf("Writing out counter as %hd\n",this->counter);
  this->accessor.putShort("counter",this->counter);
  return(status);
}
