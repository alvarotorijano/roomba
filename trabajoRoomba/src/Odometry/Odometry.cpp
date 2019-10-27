
#include "../../sensorPack_t.hpp"

#include "Odometry.hpp"

#define UNITS_ROOMBA_360_DEGREES 31900
#define UNITS_ROOMBA_100_CM 1

// Constructor 
Odometry::Odometry() {
  positionX = 0;
  positionY = 0;
  angle = 0;

  angleOriginal = 0;
}

// Destructor
Odometry::~Odometry() {

}

// Actualiza los datos internos de la posición a través de los sensores de Roomba
void Odometry::update(sensorPack_t sensor) {
  angleOriginal += (double) angle;
  angle += roombaAngleToDegrees((double) sensor.angle);
  angle = fmod(angle, 360);
  while (angle < 0) {
    angle += 360.0;
  }

  positionX += sensor.distance * cos(degreesToRadians(angle));
  positionY += sensor.distance * sin(degreesToRadians(angle));
}


double Odometry::radiansToDegrees(double radians) {
  return (radians * 4068) / 71;
}

double Odometry::degreesToRadians(double degrees) {
  return (degrees * 71) / 4068;
}


double Odometry::roombaAngleToDegrees(double angle) {
  return angle * (360.0 / (double)UNITS_ROOMBA_360_DEGREES );
}

double Odometry::degreesToRoombaAngle(double degrees) {
  return angle * ((double)UNITS_ROOMBA_360_DEGREES / 360);
}

double Odometry::roombaDistanceToCm(double roombaDistance) {
  return (roombaDistance / (double) UNITS_ROOMBA_100_CM);
}