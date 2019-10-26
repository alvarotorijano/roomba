// software serial #1: RX = digital pin 10, TX = digital pin 11



#include <SoftwareSerial.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library

#include "src/Leonidas.hpp"

#include "src/SerialUtils/SerialUtils.hpp"

/*-----( Declare Constants )-----*/
#define I2C_ADDR    0x27  // Direccion I2C para PCF8574A que es el que lleva nuestra placa dise�ada por MJKDZ
//definimos las constantes para esta placa

#define USB_BAUDRATE 9600

#define  LED_OFF  0
#define  LED_ON  1

//mjkdz i2c LCD board
//                   addr, en,rw,rs,d4,d5,d6,d7,bl, blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


#define TX_ROOMBA_PIN 4
#define RX_ROOMBA_PIN 3

#define FULL_TURN_TIME 3303

#define SENSOR_REFRESH_RATE 250

SoftwareSerial mySerial(TX_ROOMBA_PIN, RX_ROOMBA_PIN);

Leonidas leonidas(mySerial, lcd);

void setup() {
  // Open serial communications and wait for port to open:
    Serial.begin(USB_BAUDRATE);
    // Inicializar el USB
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Leonidas Bot");

    mySerial.begin(115200);
    leonidas.start();
}

void loop() {
    static unsigned long lastMillis = millis();
    unsigned long currentMillis = millis();
    leonidas.update(lastMillis - currentMillis);
    lastMillis = currentMillis;
    /*CliffSensors cliffs;
    roomba->getCliffs(&cliffs);
    char str[20];

    if (cliffs.cliffFrontLeft || cliffs.cliffFrontRight || cliffs.cliffLeft || cliffs.cliffRight) {
        roomba->stop();
        lcd.clear();
        sprintf(str, "%02x %02x %02x %02x", cliffs.cliffFrontLeft, cliffs.cliffFrontRight, cliffs.cliffLeft, cliffs.cliffRight);
        lcd.print(str);
        //lcd.print("Que me caigo!");
        while (1);
    }
    lcd.clear();
    sprintf(str, "%02x", roomba->getLightBumper());
    lcd.print(str);
    // blank line to separate data from the two ports:
    // Serial.println();
    */
    delay(1);
}
