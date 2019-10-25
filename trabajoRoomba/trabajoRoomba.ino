/*
  Software serial multple serial test

  Receives from the two software serial ports,
  sends to the hardware serial port.

  In order to listen on a software port, you call port.listen().
  When using two software serial ports, you have to switch ports
  by listen()ing on each one in turn. Pick a logical time to switch
  ports, like the end of an expected transmission, or when the
  buffer is empty. This example switches ports when there is nothing
  more to read from a port

  The circuit:
  Two devices which communicate serially are needed.
   First serial device's TX attached to digital pin 10(RX), RX to pin 11(TX)
   Second serial device's TX attached to digital pin 8(RX), RX to pin 9(TX)

  Note:
  Not all pins on the Mega and Mega 2560 support change interrupts,
  so only the following can be used for RX:
  10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

  Not all pins on the Leonardo support change interrupts,
  so only the following can be used for RX:
  8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

  created 18 Apr. 2011
  modified 19 March 2016
  by Tom Igoe
  based on Mikal Hart's twoPortRXExample

  This example code is in the public domain.

*/

// software serial #1: RX = digital pin 10, TX = digital pin 11


#define _SS_MAX_RX_BUFF 90 // RX buffer size
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LCD.h><z
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library

/*-----( Declare Constants )-----*/
#define I2C_ADDR    0x27  // Direccion I2C para PCF8574A que es el que lleva nuestra placa dise�ada por MJKDZ
//definimos las constantes para esta placa

#define USB_BAUDRATE 9600

#define  LED_OFF  0
#define  LED_ON  1

#define TX_ROOMBA_PIN 4
#define RX_ROOMBA_PIN 3
#define DETECTION_THRESHOLD 15000

#define SAFE true
#define FULL false

#define FULL_TURN_TIME 3303

#define SENSOR_REFRESH_RATE 250

//mjkdz i2c LCD board
//                   addr, en,rw,rs,d4,d5,d6,d7,bl, blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int16_t angulo;

typedef struct sensors {
	uint8_t bumpsWheelDrops;
	byte wall;
	byte cliffLeft;
	byte cliffFrontLeft;
	byte cliffFrontRight;
	byte cliffRight;
	byte virtualWall;
	byte overcurrents;
	byte dirtDetect;
	byte unused1;
	byte irOpCode;
	byte buttons;
	int16_t distance;	//Acumulative
	int16_t angle;		//Acumulative
	byte chargingState;
	int16_t voltage;
	int16_t current;
	int8_t temperature;
	uint16_t batteryCharge;
	uint16_t batteryCapacity;
	uint16_t wallSignal;
	uint16_t cliffLeftSignal;
	uint16_t cliffFrontLeftSignal;
	uint16_t cliffFrontRightSignal;
	uint16_t cliffRightSignal;
	byte unused2;
	int16_t unused3;
	byte chargerAvailable;
	byte openInterfaceMode;
	byte songNumber;
	byte songPlaying;
	byte OIStreamNumPackets;
	int16_t velocity;
	int16_t radius;
	int16_t velocityRight;
	int16_t velocityLeft;
	uint16_t encoderCountsLeft;  //Acumulative
	uint16_t encoderCountsRight; //Acumulative
	byte lightBumper;
	uint16_t lightBumpLeft;
	uint16_t lightBumpfrontLeft;
	uint16_t lightBumpCenterLeft;
	uint16_t lightBumpCenterRight;
	uint16_t lightBumpfrontRight;
	uint16_t lightBumpRight;
	byte irOPCodeLeft;
	byte irOPCodeRight;
	int16_t leftMotorCurrent;
	int16_t rightMotorCurrent;
	int16_t mainBrushCurrent;
	int16_t sideBrushCurrent;
	byte stasis;
} sensorPack_t;

SoftwareSerial myseruial(TX_ROOMBA_PIN, RX_ROOMBA_PIN);

void updateState(sensorPack_t reading, sensorPack_t* state) {
	reading.encoderCountsLeft += state->encoderCountsLeft;
	reading.encoderCountsRight += state->encoderCountsRight;
	reading.distance += state->distance;
	reading.angle += state->angle;
	*state = reading;
}

void roombaInit(bool safe) {
	byte start[3] = { 128, 130, 132 };
	/*
	  if (safe) {
	  start[1] = 130;
	  }
	*/
	myseruial.write(start, 3);
}

void stopMoving() {
	byte stop[5] = { 137, 0, 0, 0, 0 };
	myseruial.write(stop, 5);
}

// Comienza el movimiento velocidad tiene que estar en -500 a 500 mm/s y el angulo entre -2000 y 2000 mm
void drive(uint16_t velocity, uint16_t angle) {
	byte Hvelocity = velocity & 0xFF00;
	byte Lvelocity = velocity & 0x00FF;

	byte Hangle = angle & 0xFF00;
	byte Langle = angle & 0x00FF;

	byte data[5] = {
	  137, // Comando de mover
	  Hvelocity, Lvelocity, // 2 bytes de velocidad
	  Hangle, Langle // 2 bytes de angulo
	};
	myseruial.write(data, 5);
}

void turnDegree(int degree, bool direction) {
	byte clockwise[5] = { 137, 0, 255, 255, 255 };
	byte counterClockwise[5] = { 137, 0, 255, 0, 1 };
	if (direction) {
		myseruial.write(clockwise, 5);
	}
	else {
		myseruial.write(counterClockwise, 5);
	}
	delay((degree / 360) * FULL_TURN_TIME);
	stopMoving();
}

int16_t readAngle() {
	byte angleRead[2] = { 142, 20 };
	byte MSB, LSB;
	myseruial.write(angleRead, 2);
	while (myseruial.available() < 2) {
		delay(200);
	}

	MSB = myseruial.read();
	LSB = myseruial.read();

	return (int16_t(MSB << 8 | LSB));
}

sensorPack_t readSensors() {
	sensorPack_t reading;
	byte readSensorPack6[2] = { 142, 6 };
	byte readSensorPack101[2] = { 142, 101 };
	byte buffert[120]; //Would be possible to use buffer[sizeof(...)] after the C99 standar
	byte i = 0;

	myseruial.write(readSensorPack6, 2);
	delay(20);

	while (myseruial.available()) {
		buffert[i++] = myseruial.read();
	}

	myseruial.write(readSensorPack101, 2);
	delay(20);

	while (myseruial.available()) {
		buffert[i++] = myseruial.read();
	}


	memcpy(&reading, buffert, i);
	Serial.print("Estos son mis bytes: ");
	Serial.print(i);
	return reading;
}

void readSensors(sensorPack_t* data) {
	(*data) = readSensors();
}

/*
  void showSensors(sensorPack_t data) {
	char salida[1300];
	memset(salida, 0, 1300);
	sprintf(salida, "\n sWheelDrops: %d\n : %d\n fLeft: %d\n fFroeft: %d\n fFht: %d\n fRight: %d\n ualWall: %d\n cus: %d\n Dt: %d\n ed1: %d\n Code: %d\n ons: %d\n ance : %d\n e : %d\n gingState: %d\n age: %d\n ent: %d\n erature: %d\n eryCharge: %d\n eryCapacity: %d\n Signal: %d\n fLeftSignal: %d\n fFrnal: %d\n fFrognal: %d\n fRal: %d\n ed2: %d\n ed3: %d\n geable: %d\n Ide: %d\n Number: %d\n Playing: %d\n rekets: %d\n city: %d\n us: %d\n cityRight: %d\n cityLeft: %d\n derCosLeft : %d\n derRight : %d\n tBper: %d\n tBpLeft: %d\n tBptLeft: %d\n tBpCenft: %d\n tBpCeht: %d\n tBumpfRight: %d\n tBumpRight: %d\n CodeLeft: %d\n CodeRight: %d\n Morent: %d\n tMott: %d\n Brent: %d\n Brt: %d\n is: %d", data.bumpsWheelDrops, data.wall, data.cliffLeft, data.cliffFrontLeft, data.cliffFrontRight, data.cliffRight, data.virtualWall, data.overcurrents, data.dirtDetect, data.unused1, data.irOpCode, data.buttons, data.distance, data.angle, data.chargingState, data.voltage, data.current, data.temperature, data.batteryCharge, data.batteryCapacity, data.wallSignal, data.cliffLeftSignal, data.cliffFrontLeftSignal, data.cliffFrontRightSignal, data.cliffRightSignal, data.unused2, data.unused3, data.chargerAvailable, data.openInterfaceMode, data.songNumber, data.songPlaying, data.OIStreamNumPackets, data.velocity, data.radius, data.velocityRight, data.velocityLeft, data.encoderCountsLeft, data.encoderCountsRight, data.lightBumper, data.lightBumpLeft, data.lightBumpfrontLeft, data.lightBumpCenterLeft, data.lightBumpCenterRight, data.lightBumpfrontRight, data.lightBumpRight, data.irOPCodeLeft, data.irOPCodeRight, data.leftMotorCurrent, data.rightMotorCurrent, data.mainBrushCurrent, data.sideBrushCurrent, data.stasis);
	Serial.print(salida);
  }
*/

void setup() {
	static sensorPack_t state;
	// Open serial communications and wait for port to open:
	Serial.begin(USB_BAUDRATE);
	myseruial.begin(115200);

	Serial.println("Leonidas bot");
	lcd.begin(16, 2); // inicializar lcd
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("  Leonidas Bot");

	roombaInit(FULL);
	delay(100);
	//turnDegree(360, true);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Leyendo sensores");
	delay(2000);
	state = readSensors(); //reset senswor readings
	//showSensors(state);

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Buscando: ");
	delay(2000);
	//byte clockwise[5] = { 137, 0, 25, 255, 255 };
	//myseruial.write(clockwise, 5);
	//delay(5000);
	//drive(25, 0xffff);
	//delay(5000);
}

void showIr(sensorPack_t state) {
	myseruial.println("lightBumpLeft: ");
	myseruial.print(state.lightBumpLeft);
	myseruial.println("lightBumpfrontLeft: ");
	myseruial.print(state.lightBumpfrontLeft);
	myseruial.println("lightBumpCenterLeft: ");
	myseruial.print(state.lightBumpCenterLeft);
	myseruial.println("lightBumpCenterRight: ");
	myseruial.print(state.lightBumpCenterRight);
	myseruial.println("lightBumpfrontRight: ");
	myseruial.print(state.lightBumpfrontRight);
	myseruial.println("lightBumpRight: ");
	myseruial.print(state.lightBumpRight);
}

enum strategy {
	START = 0, SEEK, FACE, PUSH, CENTER
};

void loop() {
	static bool updated = false;
	byte clockwise[5] = { 137, 0, 25, 255, 255 };
	static enum strategy phase = START;
	static long double last_sensor_reading = millis(), last_lcd_update = millis();
	static sensorPack_t state;
	int i;

	if ((millis() - last_sensor_reading) > SENSOR_REFRESH_RATE) {
		updateState(readSensors(), &state);
		last_sensor_reading = millis();
	}

	if ((millis() - last_lcd_update) > SENSOR_REFRESH_RATE) {

		lcd.setCursor(0, 1);
		lcd.print("                ");
		lcd.setCursor(0, 1);
		lcd.print(state.lightBumpRight);

		last_lcd_update = millis();
	}

	if (state.cliffFrontLeft || state.cliffFrontRight || state.cliffLeft || state.cliffRight) {
		stopMoving();
		lcd.clear();
		lcd.print("Que me caigo!");
		while (1);
	}

	switch (phase) {
	case START:
		if (!updated) {
			lcd.clear();
			lcd.print("Start");
			updated = true;
		}

		myseruial.write(clockwise, 5);
		delay(2000);
		phase = SEEK;
		updated = false;
		break;

	case SEEK:
		if (!updated) {
			lcd.setCursor(0, 0);
			lcd.print("SEEK         ");
			updated = !updated;
		}
		if (state.lightBumpRight > DETECTION_THRESHOLD) {
			stopMoving();
			lcd.setCursor(0, 0);
			lcd.print("Found");
			delay(5000);
			phase = FACE;
			updated = false;
		}
		break;

	case FACE:
		if (!updated) {
			lcd.clear();
			lcd.print("Face");
			updated = !updated;
		}
		turnDegree(60, false);
		phase = PUSH;
		updated = false;
		break;

	case PUSH:
		if (!updated) {
			lcd.clear();
			lcd.print("Pushing");
			updated = !updated;
		}
		drive(25, 0);
		delay(2000);
		break;

	}

	
	delay(1);

}
