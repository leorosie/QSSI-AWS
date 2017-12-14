#pragma once
//#include "mbedtls/esp_debug.h"
#include <WiFi.h>
#include "NVS_container.h"
#include "utils.h"

/**
* \var WEB_SERVER_TIME
* \brief Roughly the amount of time the server will be awake.
*/
const int32_t WEB_SERVER_TIME = 60;

class Wifi_container {
public:

  /**
  * \brief Ready the object for use.
  * \return status (0 -> ok, !0 -> error)
  *
  * We're putting most of the interesting portions of this code into little
  * private helper functions; this is because this problem has a lot of
  * parts that don't strictly belong to any hardware (e.g. making an html doc).
  */
  int8_t setup();

  /**
  * \brief Host the connection (loop until done).
  * \return status (0 -> ok, !0 -> error)
  *
  * this serves as our 'main loop' once we're running. We need to handle
  * clients, serve page(s), and keep track of when we're supposed to shut down.
  */
  int8_t host();

  /**
  * \brief Check if the server is active.
  * \return status (1 -> on, 0 -> off)
  *
  * This will probably just throw error codes in the event that something
  * doesn't wake up properly.
  */
  int8_t is_active();

  /**
  * \brief Close all of the active connections to go back to sleep.
  * \return status (0 -> ok, !0 -> error)
  *
  * Basically, make sure everything is out of the way so the system can turn
  * off. Having a unique method for this might be overkill...
  */
  int8_t close();

  /**
  * \var data
  * \brief A copy of the NVS data we want to share.
  * TODO: this bothers me since it's basically the same struct we use in NVS.
  *       it would be nice if we could DRY this up somehow.
  */
  struct Data {
    uint8_t time_buf [64];
    uint8_t temp_buf [64];
    uint8_t snow_buf [64];
    uint8_t pyro_buf [64];
  } data;

private:

  /**
  * \brief Opens the WiFi access point.
  * \return status (0 -> ok, !0 -> error)
  *
  * This is simpler than expected because it's so well wrapped by the Arduino
  * library but we'll keep it separate in case we need to change it later.
  */
  int8_t open_access_point();

  /**
  * \brief Set up the actual web server.
  * \return status (0 -> ok, !0 -> error)
  *
  * The web server just send our ready page to the client. It would be nice if
  * we could force a redirect on the client to our page, but that may be beyond
  * our reach at the moment.
  */
  int8_t make_web_server();

  /**
  * \brief Build the document.
  * \return status (0 -> ok, !0 -> error)
  *
  * This method needs to get data out of NVS, put our information into a buffer,
  * and then make it available to the web server.
  */
  int8_t make_html_doc();

  /**
  * \brief Put some test data in to make an html page.
  * \return status (0 -> ok, !0 -> error)
  *
  * This is purely for testing purposes to make it easier on developers:
  * pack some values into this object's data struct so we can check the web
  * server's functionality.
  */
  int8_t pack_dummy_data();

  /**
  * \var ssid
  * \brief SSID for our wifi access point.
  */
  const String ssid = "QSSI-AWS";

  /**
  * \var password
  * \brief Password for our wifi access point.
  *
  * NOTE: a password must be a minimum of 8 characters or the AP will not work!!
  */
  const String password = "12345678";

  /**
  * \var ip
  * \brief IP address used by this access point.
  *
  * NOTE default IP is 192.168.4.1
  */
  IPAddress ip;

  /**
  * \var server
  * \brief The actual server that uses the access point.
  */
  WiFiServer* server;

  /**
  * \var html_page
  * \brief The string that composes our html page.
  */
  String html_page;

  /**
  * \var timecount
  * \brief Time that the web server should stay up.
  */
  int32_t timecount = WEB_SERVER_TIME;

};
