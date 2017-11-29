#include "Wifi_container.h"

//TODO is this ok?
int8_t Wifi_container::setup(){
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
  while(count < this->timecount){
    client = this->server->available();
    if (client) {
      while (client.connected()) {
        if (client.available()) {
          client.print(this->html_page);
          break;
        }
      }
    }
    delay(1000);
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
  //TODO add other objects we need to destroy
  delete(this->server);
}

int8_t Wifi_container::open_access_point(){
  int8_t status = 0;
  WiFi.softAP(this->ssid, this->password);
  this->ip = WiFi.softAPIP();
  // NOTE default IP is 192.168.4.1
  return(status);
}

int8_t Wifi_container::make_web_server(){
  int8_t status = 0;
  WiFiServer* server = new WiFiServer(80);
  this->server = server;
  //TODO do we need to check if the AP is ready??
  this->server->begin();
  return(status);
}

int8_t Wifi_container::make_html_doc(){
  uint8_t status = 0;
  char index_buf[1024];
  long time = bytes_to_long(this->data.time_buf);
  float temp = bytes_to_float(this->data.temp_buf);
  long snow = bytes_to_long(this->data.snow_buf);
  float pyro = bytes_to_float(this->data.pyro_buf);
  //wow, this is really ugly but it seems to work...
  snprintf(index_buf, sizeof(index_buf),
      R"======(
        HTTP/1.1 200 OK
        Content-type:text/html
        <html>
        <head><title>QSSI-AWS Status</title></head>
        <body>
        <center><h1><b>Last Measurement in AWS:</b></h1></center>
        <center><p>Timestamp: %s<\p><\center>
        <center><p>Temperature: %s<\p><\center>
        <center><p>Snow distance: %s<\p><\center>
        <center><p>Shortwave radiation: %s<\p><\center>
        </body>
        </html>
      )======", time, temp, snow, pyro);
  // NOTE make sure we have control over this memory!
  this->html_page = index_buf;
  return(status);
}
