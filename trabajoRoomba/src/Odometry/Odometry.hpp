#include "../../sensorPack_t.hpp"


#ifndef ODOMETRY
#define ODOMETRY



// Clase para facilitar el envío de datos recibidos por el puerto serie.
class Odometry
{
public:
    // Construnctor
    Odometry();

    // Destructor
    ~Odometry();


    // Posición en X desde el punto inicial
    double positionX;

    // Posición en Y (perpendicular a X) desde el punto inicial
    double positionY;

    // Ángulo en grados que indica cuánto se ha girado desde el inicio
    double angle;

    double angleOriginal;


    // Actualiza los datos internos de la posición a través de los sensores de Roomba
    void update(sensorPack_t sensor);

private:
    double radiansToDegrees(double radians);
    double degreesToRadians(double degrees);
    double roombaAngleToDegrees(double angle);
    double degreesToRoombaAngle(double degrees);
    double roombaDistanceToCm(double roombaDistance);
};




#endif