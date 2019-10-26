
#include "SerialUtils.hpp"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

// Constructor
SerialUtils::SerialUtils(){
    SerialInitialized = true;
}

// Destructor
SerialUtils::~SerialUtils() {

}

// Envias los datos de sensores por el puerto serie
void SerialUtils::sendData(Sensors &sensors) {
	if (!SerialInitialized) {
		Serial.begin(9600);
		SerialInitialized = true;
	}

	Serial.println("START");
    Serial.print("bumpsWheelDrops: "); // uint8_t
    Serial.println(sensors.bumpsWheeldrops);
    Serial.print("wall: "); // byte
    Serial.println(sensors.wall);
    Serial.print("cliffLeft: "); // byte
    Serial.println(sensors.cliffLeft);
    Serial.print("cliffFrontLeft: "); // byte
    Serial.println(sensors.cliffFrontLeft);
    Serial.print("cliffFrontRight: "); // byte
    Serial.println(sensors.cliffFrontRight);
    Serial.print("cliffRight: "); // byte
    Serial.println(sensors.cliffRight);
    Serial.print("virtualWall: "); // byte
    Serial.println(sensors.virtualWall);
    Serial.print("overcurrents: "); // byte
    Serial.println(sensors.overcurrents);
    Serial.print("dirtDetect: "); // byte
    Serial.println(sensors.dirtDetect);
    Serial.print("unused1: "); // byte
    Serial.println(sensors.unused1);
    Serial.print("irOpCode: "); // byte
    Serial.println(sensors.irOpcode);
    Serial.print("buttons: "); // byte
    Serial.println(sensors.buttons);
    Serial.print("distance;: "); // int16_t
    Serial.println(sensors.distance);
    Serial.print("angle: "); // int16_t
    Serial.println(sensors.angle);
    Serial.print("chargingState: "); // byte
    Serial.println(sensors.chargingState);
    Serial.print("voltage: "); // int16_t
    Serial.println(sensors.voltage);
    Serial.print("current: "); // int16_t
    Serial.println(sensors.current);
    Serial.print("temperature: "); // int8_t
    Serial.println(sensors.temperature);
    Serial.print("batteryCharge: "); // uint16_t
    Serial.println(sensors.batteryCharge);
    Serial.print("batteryCapacity: "); // uint16_t
    Serial.println(sensors.batteryCapacity);
    Serial.print("wallSignal: "); // uint16_t
    Serial.println(sensors.wallSignal);
    Serial.print("cliffLeftSignal: "); // uint16_t
    Serial.println(sensors.cliffLeftSignal);
    Serial.print("cliffFrontLeftSignal: "); // uint16_t
    Serial.println(sensors.cliffFrontLeftSignal);
    Serial.print("cliffFrontRightSignal: "); // uint16_t
    Serial.println(sensors.cliffFrontRightSignal);
    Serial.print("cliffRightSignal: "); // uint16_t
    Serial.println(sensors.cliffRightSignal);
    Serial.print("unused2: "); // byte
    Serial.println(sensors.unused2);
    Serial.print("unused3: "); // int16_t
    Serial.println(sensors.unused3);
    Serial.print("chargerAvailable: "); // byte
    Serial.println(sensors.chargerAvailable);
    Serial.print("openInterfaceMode: "); // byte
    Serial.println(sensors.openInterfaceMode);
    Serial.print("songNumber: "); // byte
    Serial.println(sensors.songNumber);
    Serial.print("songPlaying: "); // byte
    Serial.println(sensors.songPlaying);
    Serial.print("OIStreamNumPackets: "); // byte
    Serial.println(sensors.oiStreamNumPackets);
    Serial.print("velocity: "); // int16_t
    Serial.println(sensors.velocity);
    Serial.print("radius: "); // int16_t
    Serial.println(sensors.radius);
    Serial.print("velocityRight: "); // int16_t
    Serial.println(sensors.velocityRight);
    Serial.print("velocityLeft: "); // int16_t
    Serial.println(sensors.velocityLeft);
    Serial.print("encoderCountsLeft;: "); // uint16_t
    Serial.println(sensors.encoderCountsLeft);
    Serial.print("encoderCountsRight: "); // uint16_t
    Serial.println(sensors.encoderCountsRight);
    Serial.print("lightBumper: "); // byte
    Serial.println(sensors.lightBumper);
    Serial.print("lightBumpLeft: "); // uint16_t
    Serial.println(sensors.lightBumpLeft);
    Serial.print("lightBumpfrontLeft: "); // uint16_t
    Serial.println(sensors.lightBumpFrontLeft);
    Serial.print("lightBumpCenterLeft: "); // uint16_t
    Serial.println(sensors.lightBumpCenterLeft);
    Serial.print("lightBumpCenterRight: "); // uint16_t
    Serial.println(sensors.lightBumpCenterRight);
    Serial.print("lightBumpfrontRight: "); // uint16_t
    Serial.println(sensors.lightBumpFrontRight);
    Serial.print("lightBumpRight: "); // uint16_t
    Serial.println(sensors.lightBumpRight);
    Serial.print("irOPCodeLeft: "); // byte
    Serial.println(sensors.irOpcodeLeft);
    Serial.print("irOPCodeRight: "); // byte
    Serial.println(sensors.irOpcodeRight);
    Serial.print("leftMotorCurrent: "); // int16_t
    Serial.println(sensors.leftMotorCurrent);
    Serial.print("rightMotorCurrent: "); // int16_t
    Serial.println(sensors.rightMotorCurrent);
    Serial.print("mainBrushCurrent: "); // int16_t
    Serial.println(sensors.mainBrushCurrent);
    Serial.print("sideBrushCurrent: "); // int16_t
    Serial.println(sensors.sideBrushCurrent);
    Serial.print("stasis: "); // byte
    Serial.println(sensors.stasis);
}