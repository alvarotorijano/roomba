#ifndef SERIAL_UTILS
#define SERIAL_UTILS

#include "../OpenInterface/GroupPackets/Sensors.hpp"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

// Clase para facilitar el envío de datos recibidos por el puerto serie.
class SerialUtils
{
private:

    // Indica si el puerto serie ha sido inicilizado
    bool SerialInitialized;

public:
    // Contrunctor
    SerialUtils();

    // Destructor
    ~SerialUtils();

    // Envias los datos de sensores por el puerto serie
    void sendData(Sensors &sensors);
};




#endif