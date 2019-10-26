#include "Leonidas.hpp"

Leonidas::Leonidas(SoftwareSerial &serial, LiquidCrystal_I2C &lcd)
    : Bot(serial, lcd), seek(SeekState(this)), face(FaceState(this)),
    push(PushState(this))
{
}

void Leonidas::start() {
    Bot::start();
    roomba.start();
    roomba.setFullMode();
    roomba.stop();
    // Hacemos que las luces parpadeen para asegurarnos que funciona.
    for (int i = 0; i < 10; i++) {
        byte ledInfo1[3] = {0X0F, 0x00, 0x00};
        roomba.send(Opcode::LEDS, ledInfo1, 3);
        delay(500);
        byte ledInfo2[3] = {0X0F, 0x80, 0xFF};
        roomba.send(Opcode::LEDS, ledInfo2, 3);
        delay(500);
    }
    // Limpia los sensores de posición.
    PositionSensors positionSensors;
    roomba.getPositionSensors(&positionSensors);
    setState(&seek);
}

void Leonidas::update(unsigned long delta) {
    Bot::update(delta);
}

void Leonidas::stop() {
    Bot::stop();
}