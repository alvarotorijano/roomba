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
    // Posición en X desde el punto inicial
    double positionX;

    // Posición en Y (perpendicular a X) desde el punto inicial
    double positionY;

    // Ángulo en grados que indica cuánto se ha girado desde el inicio
    double angle;


    // Construnctor
    Odometry();

    // Destructor
    ~Odometry();

    update(sensorPack_t sensor);

};




#endif