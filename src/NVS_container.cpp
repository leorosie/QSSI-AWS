#include "NVS_container.h"

uint8_t NVS_container::setup(){
  uint8_t status;
  this->accessor.begin("AWS_data", false);
  this->zero_data();
  uint8_t sub_status = this->read_counter();
  if(sub_status != 0){
    Serial.println("no existing counter; making it now");
    this->accessor.putShort("counter", 0);
  }
  sub_status = this->read_fails();
  if(sub_status != 0){
    Serial.println("no existing fails; making it now");
    this->accessor.putShort("fails", 0);
  }
  return(status);
}

uint8_t NVS_container::close(){
  uint8_t status;
  this->write_counter();
  this->write_fails();
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
  //this->accessor.putBytes(key_buf,this->data.time_buf,sizeof(this->data.time_buf));
  this->accessor.putBytes(key_buf,this->data.time_buf,LONG_SIZE);
  // temperature
  strcpy(key_str, "temp_%hd");
  sprintf(key_buf, key_str, this->counter);
  //this->accessor.putBytes(key_buf,this->data.temp_buf,sizeof(this->data.time_buf));
  this->accessor.putBytes(key_buf,this->data.temp_buf,FLOAT_SIZE);
  // snow depth
  strcpy(key_str, "snow_%hd");
  sprintf(key_buf, key_str, this->counter);
  //this->accessor.putBytes(key_buf,this->data.snow_buf,sizeof(this->data.snow_buf));
  this->accessor.putBytes(key_buf,this->data.snow_buf,LONG_SIZE);
  // pyranometer
  strcpy(key_str, "pyro_%hd");
  sprintf(key_buf, key_str, this->counter);
  //this->accessor.putBytes(key_buf,this->data.pyro_buf,sizeof(this->data.pyro_buf));
  this->accessor.putBytes(key_buf,this->data.pyro_buf,LONG_SIZE);
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

uint16_t NVS_container::get_counter(){
  return(this->counter);
}

uint16_t NVS_container::get_fails(){
  return(this->fails);
}

uint8_t NVS_container::set_fails(uint16_t fails){
  this->fails = fails;
  return(0);
}

uint8_t NVS_container::read_fails(){
  uint8_t status = 0;
  this->fails = this->accessor.getShort("fails",0); //0 -> not found
  //if(this->fails == 0){
  //  status = -1;
  //}
  return(status);
}

uint8_t NVS_container::write_fails(){
  uint8_t status;
  Serial.printf("Writing out fails as %hd\n",this->fails);
  this->accessor.putShort("fails",this->fails);
  return(status);
}

uint8_t NVS_container::read_counter(){
  uint8_t status = 0;
  this->counter = this->accessor.getShort("counter",0); //0 -> not found
  if(this->counter == 0){
    status = -1;
  }
  return(status);
}

uint8_t NVS_container::write_counter(){
  uint8_t status;
  Serial.printf("Writing out counter as %hd\n",this->counter);
  this->accessor.putShort("counter",this->counter);
  return(status);
}

uint8_t NVS_container::clear(){
  uint8_t status = 0;
  bool is_cleared;
  is_cleared = this->accessor.clear();
  status = is_cleared ? 0 : -1;
  if(status == 0){
    Serial.printf("NVS was cleared.\n");
    this->counter = 0;
    this->write_counter();
  } else {
    Serial.printf("NVS was not cleared.\n");
  }
  return(status);
}
