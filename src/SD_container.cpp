#include "SD_container.h"

int8_t SD_container::setup(const char* path, int path_len, int card_pin){
  int8_t status = 0;
  this->card_pin = card_pin;
  if (path_len >= MAX_PATH_LEN) {
    return(-1);
  } else {
    memcpy(this->path, path, path_len);
  }
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, card_pin);
  if (!SD.begin(this->card_pin)){
    SD.end();
    SPI.end();
    return(-9);
  }
  this->filesystem = &SD;
  if ( !(this->filesystem) ) {
    return(-2);
  }
  this->file = this->filesystem->open(this->path); //make sure it can read
  if (!this->file) { //if there's no file...
    this->make_file(); //make it
    this->file = this->filesystem->open(this->path); //make sure it worked
    if (!this->file) {
      return(-3); //it didn't. something is really messed up.
    }
  }
  this->file.close(); //close this test handle...
  this->file = this->filesystem->open(this->path, FILE_APPEND); //we are ready!
  return(status);
}

int8_t SD_container::close(){
  int8_t status = 0;
  this->file.close();
  return(status);
}

int8_t SD_container::print_file(){
  int8_t status = 0;
  if( this->file.available() ) {
    status = -1;
  } else {
    while( this->file.available() ) {
      Serial.write( this->file.read() );
    }
  }
  return(status);
}

int8_t SD_container::make_file(){
  int8_t status = 0;
  this->file = this->filesystem->open(this->path, FILE_WRITE);
  if (!file){
    return(-1);
  }
  String csv_header = "timestamp(s),temperature(C),sonic_range(mm),shortwave(Wm^-2)\n";
  if( !(this->file.print(csv_header)) ) {
    return(-2);
  }
  this->file.close(); //close the test handle.
  return(status);
}

int8_t SD_container::append_to_file(String line){
  int8_t status = 0;
  if(!this->file){
    return(-1);
  }
  if(!this->file.print(line)) {
    return(-2);
  }
  return(status);
}

int8_t SD_container::make_line(NVS_container* nvs, int index){
  int8_t status = 0;
  char buffer[512];
  nvs->read_data(index);
  long time = bytes_to_long(nvs->data.time_buf);
  float temp = bytes_to_float(nvs->data.temp_buf);
  long snow = bytes_to_long(nvs->data.snow_buf);
  float pyro = bytes_to_float(nvs->data.pyro_buf);
  snprintf(buffer, sizeof(buffer), "%ld,%f,%ld,%f", time, temp, snow, pyro);
  String line = buffer;
  String newline = " \n";
  this->append_to_file(line);
  this->append_to_file(newline);
  nvs->zero_data();
  return(status);
}
