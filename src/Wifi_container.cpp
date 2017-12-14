#include "Wifi_container.h"

int8_t Wifi_container::setup(){
  //this->pack_dummy_data();
  int8_t status;
  status = this->make_html_doc();
  status = this->open_access_point();
  status = this->make_web_server();
  return(status);
}

int8_t Wifi_container::host(){
  int8_t status = 0;
  int8_t count = 0;
  WiFiClient client;
  while(count < (this->timecount * 100)){
    client = this->server->available();
    if (client) {
      while (client.connected()) {
        client.print(this->html_page);
        break;
      }
    }
    delay(10);
    ++count;
  }
  client.stop();
  return(status);
}

int8_t Wifi_container::is_active(){
  if(this->server){
    return(1);
  } else {
    return(0);
  }
}

int8_t Wifi_container::close(){
  //TODO add other objects we need to destroy (if any)
  delete(this->server);
}

int8_t Wifi_container::open_access_point(){
  int8_t status = 0;
  WiFi.softAP(this->ssid.c_str(), this->password.c_str());
  this->ip = WiFi.softAPIP();
  // NOTE default IP is 192.168.4.1
  return(status);
}

int8_t Wifi_container::make_web_server(){
  int8_t status = 0;
  WiFiServer* server = new WiFiServer(80);
  this->server = server;
  this->server->begin();
  return(status);
}

int8_t Wifi_container::make_html_doc(){
  uint8_t status = 0;
  long time = bytes_to_long(this->data.time_buf);
  float temp = bytes_to_float(this->data.temp_buf);
  long snow = bytes_to_long(this->data.snow_buf);
  float pyro = bytes_to_float(this->data.pyro_buf);
  String msg = String("<!DOCTYPE html>") +
    "<html>" +
    "<head><title>QSSI-AWS Status</title></head>" +
    "<body>" +
    "<center><h1><b>Last Measurement in AWS:</b></h1></center>" +
    "<center><p>Timestamp: " + String(time) + "</p></center>"+
    "<center><p>Temperature: " + String(temp) + "</p></center>"+
    "<center><p>Snow distance: " + String(snow) + "</p></center>"+
    "<center><p>Shortwave: " + String(pyro) + "</p></center>"+
    "</body>" +
    "</html>";
  uint32_t len = msg.length();
  String res =  String("HTTP/1.1 200 OK\r\n") +
    "Content-type:text/html\r\n" +
    "Content-length: " + String(len) + "\r\n\r\n" + msg;
  this->html_page = res;
  return(status);
}

int8_t Wifi_container::pack_dummy_data(){
  uint8_t status = 0;
  int8_t len;
  long time_val = 1234;
  float temp_val = 22.3;
  long snow_val = 960;
  float pyro_val = 55.0;
  uint8_t data_buffer[64];
  //time
  len = long_to_bytes(data_buffer, time_val);
  memcpy(this->data.time_buf, &data_buffer, len);
  memset(&data_buffer, 0, sizeof(data_buffer));
  //temp
  len = float_to_bytes(data_buffer, temp_val);
  memcpy(this->data.temp_buf, &data_buffer, len);
  memset(&data_buffer, 0, sizeof(data_buffer));
  //snow
  len = long_to_bytes(data_buffer, snow_val);
  memcpy(this->data.snow_buf, &data_buffer, len);
  memset(&data_buffer, 0, sizeof(data_buffer));
  //pyro
  len = float_to_bytes(data_buffer, pyro_val);
  memcpy(this->data.pyro_buf, &data_buffer, len);
  memset(&data_buffer, 0, sizeof(data_buffer));
  return(status);
}
