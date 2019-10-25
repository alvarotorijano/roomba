// software serial #1: RX = digital pin 10, TX = digital pin 11



#include <SoftwareSerial.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library

#include "Roomba.hpp"
#include "OpenInterface/GroupPackets/Sensors.hpp"

#include "SerialUtils/SerialUtils.hpp"

/*-----( Declare Constants )-----*/
#define I2C_ADDR    0x27  // Direccion I2C para PCF8574A que es el que lleva nuestra placa dise�ada por MJKDZ
//definimos las constantes para esta placa

#define USB_BAUDRATE 9600

#define  LED_OFF  0
#define  LED_ON  1

//mjkdz i2c LCD board
//                   addr, en,rw,rs,d4,d5,d6,d7,bl, blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int16_t angulo;


#define TX_ROOMBA_PIN 4
#define RX_ROOMBA_PIN 3

#define SAFE true
#define FULL false

#define FULL_TURN_TIME 3303

#define SENSOR_REFRESH_RATE 250

SoftwareSerial mySerial(TX_ROOMBA_PIN, RX_ROOMBA_PIN);

Roomba *roomba;

void setup() {
  // Open serial communications and wait for port to open:
	Serial.begin(USB_BAUDRATE);
	lcd.begin(16, 2); // inicializar lcd
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("  Leonidas Bot");
	lcd.setCursor(0, 1);
	lcd.print(sizeof(Sensors));

	mySerial.begin(115200);
	roomba = new Roomba(mySerial);
	roomba->start();
	roomba->setFullMode();
	roomba->getAngle();
	roomba->turnDegree(360, 255);
	roomba->driveStraight(255);

	lcd.setCursor(0, 1);
	lcd.print(roomba->getAngle());
  // Start each software serial port
}

void loop() {
	CliffSensors cliffs;
	roomba->getCliffs(cliffs);

	if (cliffs.cliffFrontLeft || cliffs.cliffFrontRight || cliffs.cliffLeft || cliffs.cliffRight) {
		roomba->stop();
	}

	// blank line to separate data from the two ports:
	// Serial.println();

	delay(1);
}
