#include "AbstractSensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

class TemperatureSensor: public AbstractSensor {
public:

  /**
  *
  */
  int8_t setup();

  /**
  *
  */
  uint8_t* read();

  /**
  *
  */
  void printTemperature();

  /**
  *
  */
  void printAddress();

  /**
  *
  */
  void printAlarms();

  /**
  *
  */
  void printData();

  /**
  *
  */
  void checkAlarm();
private:
  DeviceAddress insideThermometer;
  OneWire oneWire;
  DallasTemperature dt_sensor;
};
