#include "Leonidas.hpp"

#include <math.h>

#define FULL_TURN_READ 30873.0

Leonidas::Leonidas(SoftwareSerial &serial, LiquidCrystal_I2C &lcd)
    :   
        Bot(serial, lcd), 
        seek(SeekState(this)), 
        face(FaceState(this)),
        push(PushState(this)), 
        angle(0), x(0), y(0),
        calibrateAngle(CalibrateAngleState(this)), 
        menu(MenuState(this)),
        dummy(DummyState(this)),
        calibrateDistance(CalibrateDistanceState(this)),
        squareSide(SquareSideState(this)),
        squareCorner(SquareCornerState(this))
{
}

void Leonidas::start() {
    Bot::start();
    roomba.start();
    roomba.setFullMode();
    roomba.stop();
    // Hacemos que las luces parpadeen para asegurarnos que funciona.
    for (int i = 0; i < 2; i++) {
        byte ledInfo1[3] = {0x0F, 0x00, 0x00};
        roomba.send(Opcode::LEDS, ledInfo1, 3);
        delay(500);
        byte ledInfo2[3] = {0x0F, 0x80, 0xFF};
        roomba.send(Opcode::LEDS, ledInfo2, 3);
        delay(500);
    }
    // Limpia los sensores de posición.
    PositionSensors positionSensors;
    roomba.getPositionSensors(&positionSensors);
    setState(&menu);
    lastRead = millis();
}

void Leonidas::update(unsigned long delta) {
    if (millis() - lastRead >= 1000) {
        lastRead = millis();
        PositionSensors positionSensors;
        roomba.getPositionSensors(&positionSensors);
        odometry.add(positionSensors.angle, positionSensors.distance);
        lcd.setCursor(0, 1);
        lcd.print(odometry.getDegree());
        lcd.print(" ");
        lcd.print(odometry.getX());
        lcd.print(" ");
        lcd.print(odometry.getY());
    }
    Bot::update(delta);
}

void Leonidas::stop() {
    Bot::stop();
}