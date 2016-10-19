/*

This is example for Texas Instruments OPT3002 Light to Digital Sensor Arduino Library
ClosedCube OPT3002 Light to Digital Sensor breakout module

Written by AA for ClosedCube

Initial Date: 12-Oct-2016

Hardware connections for Arduino Uno:
VDD to 3.3V DC
SDA to A4
SCL to A5
GND to common ground

MIT License

*/

#include <Wire.h>
#include "ClosedCube_OPT3002.h"

ClosedCube_OPT3002 opt3002;

#define OPT3002_ADDRESS 0x45

void setup()
{
	Serial.begin(9600);
	Serial.println("ClosedCube OPT3002 Arduino Test");

	opt3002.begin(OPT3002_ADDRESS);
	Serial.print("OPT3002 Manufacturer ID:");
	Serial.print(opt3002.readManufacturerID());
	Serial.print(" Device ID:");
	Serial.println(opt3002.readDeviceID());

	configureSensor();
	printResult("High-Limit", opt3002.readHighLimit());
	printResult("Low-Limit", opt3002.readLowLimit());
	Serial.println("----");
}

void loop()
{
	OPT3002 result = opt3002.readResult();
	printResult("OPT3002", result);
	delay(500);
}

void printResult(String text, OPT3002 result) {
	if (result.error == NO_ERROR) {
		Serial.print(text);
		Serial.print(": ");
		Serial.print(result.lux);
		Serial.println(" nW/cm2");
	}
	else {
		printError(text, result.error);
	}
}

void printError(String text, OPT3002_ErrorCode error) {
	Serial.print(text);
	Serial.print(": [ERROR] Code #");
	Serial.println(error);
}

void configureSensor() {
	OPT3002_Config newConfig;

	newConfig.RangeNumber = B1100;
	newConfig.ConvertionTime = B0;
	newConfig.Latch = B1;
	newConfig.ModeOfConversionOperation = B11;

	OPT3002_ErrorCode errorConfig = opt3002.writeConfig(newConfig);
	if (errorConfig != NO_ERROR)
		printError("OPT3002 configuration", errorConfig);
	else {
		OPT3002_Config sensorConfig = opt3002.readConfig();
		Serial.println("OPT3002 Current Config:");
		Serial.println("------------------------------");

		Serial.print("Conversion ready (R):");
		Serial.println(sensorConfig.ConversionReady, HEX);

		Serial.print("Conversion time (R/W):");
		Serial.println(sensorConfig.ConvertionTime, HEX);

		Serial.print("Fault count field (R/W):");
		Serial.println(sensorConfig.FaultCount, HEX);

		Serial.print("Flag high field (R-only):");
		Serial.println(sensorConfig.FlagHigh, HEX);

		Serial.print("Flag low field (R-only):");
		Serial.println(sensorConfig.FlagLow, HEX);

		Serial.print("Latch field (R/W):");
		Serial.println(sensorConfig.Latch, HEX);

		Serial.print("Mask exponent field (R/W):");
		Serial.println(sensorConfig.MaskExponent, HEX);

		Serial.print("Mode of conversion operation (R/W):");
		Serial.println(sensorConfig.ModeOfConversionOperation, HEX);

		Serial.print("Polarity field (R/W):");
		Serial.println(sensorConfig.Polarity, HEX);

		Serial.print("Overflow flag (R-only):");
		Serial.println(sensorConfig.OverflowFlag, HEX);

		Serial.print("Range number (R/W):");
		Serial.println(sensorConfig.RangeNumber, HEX);

		Serial.println("------------------------------");
	}

}

