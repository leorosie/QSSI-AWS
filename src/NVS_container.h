#pragma once
#include <Preferences.h>
#include "utils.h"

extern const uint8_t FLOAT_SIZE;
extern const uint8_t LONG_SIZE;

/** \var MAX_NVS_COUNTER
*   \brief Max number of entries in NVS before we move data to SD card.
*/
const uint8_t MAX_NVS_COUNTER = 24;

class NVS_container {
public:

  /**
  * \brief Setup for use.
  * \return status (0 -> success, other -> failure)
  *
  * If there is no counter in the NVS, make it now. Make namespace. Zero data.
  * Do anything we need to ensure we're ready for reading/writing.
  */
  uint8_t setup();

  /**
  * \brief Close before system reset.
  * \return status (0 -> success, -1 -> failure)
  *
  * Fix counter, disable NVS connection, etc.
  */
  uint8_t close();

  /**
  * \brief Get a value from NVS.
  * \param index Identifier for NVS key.
  * \return status (0 -> success, -1 -> failure)
  *
  * This will pull out data from NVS and hand it to us in a usable format: as
  * members of our data `struct`. Make sure you get it out before you call it
  * again!
  */
  uint8_t read_data(uint16_t index);

  /**
  * \brief Write a value to NVS.
  * \return status (0 -> success, -1 -> failure)
  *
  * This will write everything in our data `struct` to NVS. This means of course
  * that everything needs to be written into the struct before we call this
  * method...
  */
  uint8_t write_data();

  /**
  * \brief Zero the data `struct`.
  * \return status (0 -> success, -1 -> failure)
  *
  * This will simply zero the array for our next use.
  */
  uint8_t zero_data();

  /**
  * \brief Clear all entries from NVS.
  * \return status (0 -> success, -1 -> failure)
  *
  * This is the last step of writing our data to SD card: we must make sure
  * that NVS is empty so we can write to it again.
  */
  uint8_t clear();

  /**
  * \brief Give the current value of the counter in memory.
  * \return counter The current counter of the object.
  *
  * This is needed to check whether it's time to move data from NVS -> SD.
  */
  uint16_t get_counter();

  /**
  * \brief Get the fail state for SD card writes.
  *
  * SD cards don't work very well with esp32. This is part of a hack to retry
  * bad writes.
  */
  uint16_t get_fails();

  /**
  * \brief get the fail state for SD card writes.
  *
  * SD cards don't work very well with esp32. This is part of a hack to retry
  * bad writes.
  */
  uint8_t set_fails(uint16_t fails);

  /**
  * \var data
  * \brief All fields of a single timepoint observation.
  *
  * This wraps all of our sensors and timestamp into a single package.
  * We use it for reading/writing purposes.
  */
  struct Data {
    uint8_t time_buf [64];
    uint8_t temp_buf [64];
    uint8_t snow_buf [64];
    uint8_t pyro_buf [64];
  } data;

  /**
  * \brief SD cards should be able to manipulate this class.
  * \relates SD_container
  *
  * SD cards will be able to load this class's `data` field as they need by
  * requesting particular indices from storage; it will then format the data and
  * write it to the card.
  */
  friend class SD_container;

private:

  /**
  * \brief Get the counter from NVS.
  * \return status (0 -> success, -1 -> failure)
  *
  * Internal method to fetch the NVS counter when we wake up. This is needed
  * to check whether we need to write out to SD card, name keys, etc.
  */
  uint8_t read_counter();

  /**
  * \brief Get the fails from NVS.
  * \return status (0 -> success, -1 -> failure)
  *
  * Internal method to fetch the fails field on launch. This is used to try
  * re-writing after the SD card fails.
  */
  uint8_t read_fails();

  /**
  * \brief Set the fails in NVS.
  * \return status (0 -> success, -1 -> failure)
  *
  * Internal method to update the Sd fails before sleep because we can't fix it
  * while the system is awake...
  */
  uint8_t write_fails();

  /**
  * \brief Set the counter in NVS.
  * \return status (0 -> success, -1 -> failure)
  *
  * Internal method to update the NVS counter before going to sleep. This is
  * how we keep track of the number of records we currenly have.
  */
  uint8_t write_counter();

  /**
  * \var Preferences accessor
  * \brief Access non-volatile storage with this object.
  *
  * This oddly named class gives us a nicer interface to the NVS on board the
  * ESP32. Using this, we are able to read and write most common data types
  * (though we aim to handle only `byte[]`).
  */
  Preferences accessor;

  /**
  * \var int16_t counter
  * \brief Keeps track of number of records in NVS.
  *
  * This will be used to both store and recover data from the NVS. It's needed
  * because we will run against the limits of our partition quite rapidly; we
  * need to make sure there is space and that we can get everything back out!
  * Used to name keys, keep track of writes, etc.
  */
  int16_t counter;

  /**
  * \brief Fail state for SD card writes.
  *
  * SD cards don't work very well with esp32. This is part of a hack to retry
  * bad writes.
  */
  uint16_t fails;

};
