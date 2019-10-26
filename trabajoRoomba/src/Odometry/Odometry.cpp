
#include "../../sensorPack_t.hpp"

#include "Odometry.hpp"

// Constructor 
Odometry::Odometry() {
  positionX = 0;
  positionY = 0;
  angle = 0;
}

// Destructor
Odometry::~Odometry() {

}

// Actualiza los datos internos de la posición a través de los sensores de Roomba
void Odometry::update(sensorPack_t sensor) {
  angle += sensor.angle;

  positionX += sensor.distance * cos(degreesToRadians(roombaAngleToDegrees(angle)));
  positionY += sensor.distance * sin(degreesToRadians(roombaAngleToDegrees(angle)));
}





double Odometry::radiansToDegrees(double radians) {
  return (radians * 4068) / 71;
}

double Odometry::degreesToRadians(double degrees) {
  return (degrees * 71) / 4068;
}


double Odometry::roombaAngleToDegrees(double angle) {
  return 0; // TODO
}

double Odometry::degreesToRoombaAngle(double degrees) {
  return 0; // TODO
}