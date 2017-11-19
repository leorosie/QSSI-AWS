#pragma once

#include "FS.h"
#include "SD.h"
#include "SPI.h"

#include "NVS_container.h"

/** \var MAX_PATH_LEN
*   \brief Max number of characters allowed in path.
*/
const uint8_t MAX_PATH_LEN = 128;

extern const int SCK_PIN;
extern const int MISO_PIN;
extern const int MOSI_PIN;

class SD_container{
public:

  /**
  * \brief Set up this card for writing.
  * \param path The file path to use.
  * \param card_pin The slave select for this SD card.
  * \return status (0 -> success, -1 -> failure)
  *
  * This method will wrap a lot of complex functionality. It needs to be sure
  * the SD card is alive and talking, the filesystem is valid, the path is good,
  * and more. Then it needs to inform the rest of the program that it's ready.
  */
  int8_t setup(const char* path, int path_len, int card_pin);

  /**
  * \brief Disengage the filesystem and close the SD card connection.
  * \return status (0 -> success, -1 -> failure)
  *
  * This should obviously be called when we're done using the SD card.
  */
  int8_t close();

  /**
  * \brief Read the file and print it out.
  * \return status (0 -> success, -1 -> failure)
  *
  * This is entirely for diagnostic purposes; in operation, we won't be reading
  * at all.
  */
  int8_t print_file();

  /**
  * \brief Write the file if it doesn't exist.
  * \return status (0 -> success, -1 -> failure)
  *
  * This could be called exactly one time: on system start. Every subsequent
  * operation should instead append to the file.
  */
  int8_t make_file();

  /**
  * \brief Append to the file this container tracks.
  * \return status (0 -> success, -1 -> failure)
  *
  * This should be called for each line we want to write to the file system. It
  * should be called many times every time we empty NVS.
  */
  int8_t append_to_file(String line);

  /**
  * \brief Grab data from NVS and format it into an entry for our file.
  * \return status (0 -> success, -1 -> failure)
  *
  * This method directly manipulates the NVS to populate its `data` struct
  * with whatever is stored at `index`, format a new line for the file, and then
  * append it to the file. It should be iteratively called on the NVS_container
  * from 0 to MAX_NVS_COUNTER.
  */
  int8_t make_line(NVS_container nvs, int index);

private:

  /**
  * \var FS filesystem
  * \brief A handle for the actual filesystem (once it's ready).
  *
  * We don't plan on separating things: we want one big csv with all of our
  * data. This ensures we have it all together.
  */
  FS* filesystem;

  /**
  * \var int card_pin
  * \brief The slave select pin this container uses to communicate.
  *
  * In order to invoke SD.begin() we need to have the SS pin handy. These are
  * defined as constants (and exported) in `pins.h` but these containers should
  * rely on what they are told rather than trying to find this information for
  * themselves.
  */
  int card_pin;

  /**
  * \var char[] path
  * \brief The file path to which we write/append.
  *
  * As described above, there's only one file on the SD card. Let's keep track
  * of where it is.
  */
  char path[MAX_PATH_LEN];

  /**
  * \var File file
  * \brief The file (once it's ready for use).
  *
  * This is a handle on the actual file we are using. Don't break it!
  */
  File file;

};
