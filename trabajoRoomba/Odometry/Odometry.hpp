#ifndef ODOMETRY
#define ODOMETRY

#include "../sensorPack_t.hpp"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

// Clase para facilitar el envío de datos recibidos por el puerto serie.
class Odometry
{
private:
  
public:
    // Contrunctor
    Odometry();

    // Destructor
    ~Odometry();

};




#endif