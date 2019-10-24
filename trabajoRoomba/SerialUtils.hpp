#ifndef SERIAL_UTILS
#define SERIAL_UTILS

#include "sensorPack_t.hpp"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class SerialUtils
{
private:
    bool SerialInitialized;
public:
    SerialUtils();
    ~SerialUtils();

    void sendData(sensorPack_t sensors);
};




#endif