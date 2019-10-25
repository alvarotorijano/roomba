
// Amplicamos el tamaño de buffer de SoftwareSerial 
#define _SS_MAX_RX_BUFF 90 // RX buffer size
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library

#include "Roomba.hpp"
#include "SerialUtils/SerialUtils.hpp"
#include "sensorPack_t.hpp"

/*-----( Declare Constants )-----*/
// Direccion I2C para PCF8574A (pantalla LCD)
#define I2C_ADDR    0x27
//definimos las constantes para esta placa

// Velocidad de 
#define USB_BAUDRATE 9600

#define  LED_OFF  0
#define  LED_ON  1

// Pines conectados al arduino para simular un puerto serie conectado al ROOMBA
#define TX_ROOMBA_PIN 4
#define RX_ROOMBA_PIN 3
#define DETECTION_THRESHOLD 15000

#define SAFE true
#define FULL false

// Tiempo en milisegundos a máxima velocidad que tarda en dar 360º (una vuelta completa)
#define FULL_TURN_TIME 3303

// Cada cuántos milisegundos se actualizan los sensores 
#define SENSOR_REFRESH_RATE 250


//mjkdz i2c LCD board
//                        addr, en,rw,rs,d4,d5,d6,d7,bl, blpol
LiquidCrystal_I2C lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Variable no usada por ahora
int16_t angulo;

// Simulación de puerto serie con los pines conectados al Arduino
SoftwareSerial myseruial(TX_ROOMBA_PIN, RX_ROOMBA_PIN);



// Actualiza los valores de los contadores totales son los proporcionados por Roomba
// para mantener un totalizado de movimientos y giros realizados.
void updateState(sensorPack_t reading, sensorPack_t* state) {

	//! Se está escribiendo en reading los alores de state, cuando debería escribirse en state los valores del reading
	// TODO Aquí hay que meter la lógica de almacenar la posición e ir calcuando la posición (x, y) actual; para poder volver al la posición inicial

	reading.encoderCountsLeft += state->encoderCountsLeft;
	reading.encoderCountsRight += state->encoderCountsRight;
	reading.distance += state->distance;
	reading.angle += state->angle;
	*state = reading;
}

// Inicial la conexión con Roomba en modo FULL por ahora.
void roombaInit(bool safe) {
	byte start[3] = { 128, 130, 132 };
	/*
	  if (safe) {
	  start[1] = 130;
	  }
	*/
	myseruial.write(start, 3);
}

// Detiene el movimiento
void stopMoving() {
	byte stop[5] = { 137, 0, 0, 0, 0 };
	myseruial.write(stop, 5);
}

// Comienza el movimiento velocidad tiene que estar en -500 a 500 mm/s y el angulo entre -2000 y 2000 mm
void drive(int16_t velocity, int16_t angle) {
	byte Hvelocity = (velocity >> 8) & 0x00FF;
	byte Lvelocity = velocity & 0x00FF;

	byte Hangle = (angle >> 8) & 0x00FF;
	byte Langle = angle & 0x00FF;

	byte data[5] = {
	  137, // Comando de mover
	  Hvelocity, Lvelocity, // 2 bytes de velocidad
	  Hangle, Langle // 2 bytes de angulo
	};

	myseruial.write(data, 5);
}

// Gira el robot sobre su propio eje a máxima velocidad y espera a que termina
void turnDegree(
	int degree, // Grados en los que girar
	bool direction // dirección, true para que gire en el sentido de las agujas del robot
	) {
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

// Lee el alguno que roomba cree que ha girado desde la última lectura del angulo, empieza en 0.
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

// lee todos los sensores y los devuelve en forma de estructura.
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

// Lectura de sensores a tracés de un puntero de memoria recibido.
// el punto debe apuntar a una zona de memoria reservada con el tamaño del struct.
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

void pruebaAvances() {
	lcd.print("caminando 3 segundos: ");
	delay(1000);


	drive(-25, 0);
	delay(3000);
	stopMoving();
	
	lcd.setCursor(0, 0);
	lcd.print("Leyendo sensores");
	sensorPack_t s = readSensors();
	lcd.setCursor(0, 1);

	for (int i = 100 - 1; i >= 0; i--)
	{
		switch (i % 2)
		{
			case 0:
				lcd.setCursor(0, 0);
				lcd.print("Distancia");
				lcd.setCursor(0, 1);
				lcd.print(s.distance);
			break;
			
			case 1:
				lcd.setCursor(0, 0);
				lcd.print("Angulo");
				lcd.setCursor(0, 1);
				lcd.print(s.angle);
			break;
		
			default:
			break;
		}
		delay(3000);
		lcd.clear();
	}
	
	delay(300000);

}

// Función de Arduino que se ejecuta solo una vez al inicio.
void setup() {
	static sensorPack_t state;
	// Open serial communications and wait for port to open:
	Serial.begin(USB_BAUDRATE);
	myseruial.begin(115200);

	roombaInit(FULL);
	stopMoving();

	Serial.println("Leonidas bot");
	lcd.begin(16, 2); // inicializar lcd
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Leonidas Bot  ");
	delay(500);
	lcd.setCursor(0, 0);
	lcd.print(" Leonidas Bot ");
	delay(500);
	lcd.setCursor(0, 0);
	lcd.print("  Leonidas Bot");
	delay(500);

	delay(100);
	//turnDegree(360, true);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Leyendo sensores");
	delay(2000);
	state = readSensors(); //reset senswor readings
	//showSensors(state);

	// pruebaAvances();

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Buscando: ");
}

// Envían por el puerto serie la información de los bumpers
void showIr(sensorPack_t state) {
	Serial.println("lightBumpLeft: ");
	Serial.print(state.lightBumpLeft);
	Serial.println("lightBumpfrontLeft: ");
	Serial.print(state.lightBumpfrontLeft);
	Serial.println("lightBumpCenterLeft: ");
	Serial.print(state.lightBumpCenterLeft);
	Serial.println("lightBumpCenterRight: ");
	Serial.print(state.lightBumpCenterRight);
	Serial.println("lightBumpfrontRight: ");
	Serial.print(state.lightBumpfrontRight);
	Serial.println("lightBumpRight: ");
	Serial.print(state.lightBumpRight);
}

// Enumeración con los estados que tiene la máquina de estados
enum strategy {
	START = 0, // Comienzo 
	SEEK,  // Búsqueda de objetivo
	FACE,  // Orientación del roomba
	PUSH,  // Empuje de la botella fuera de la mesa
	CENTER // Reubicación del robo la posición inicial // TODO Cambiar por volver a la posición inicial
};

// Bucle infinito de ejecución de Arduino
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
		lcd.setCursor(0, 1);
		if (state.cliffFrontLeft) {
			lcd.print("cliffFrontLeft");
		}
		if (state.cliffFrontRight) {
			lcd.print("cliffFrontRight");
		}
		if (state.cliffLeft) {
			lcd.print("cliffLeft");
		}
		if (state.cliffRight) {
			lcd.print("cliffRight");
		}
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
