
#include "Odometry.hpp"
#include "../sensorPack_t.hpp"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

// Constructor 
Odometry::Odometry() {
  positionX = 0;
  positionY = 0;
  angle = 0;
}

// Destructor
Odometry::~Odometry() {

}


Odometry::update(sensorPack_t sensor) {
  // TODO gestionar lógica
}