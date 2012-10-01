/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "PersonDetector.h"

const byte SENSOR_PIN = A0; //use the thermistor @ Arduino pin Analog 0
int min            = 0;
int lowThreshold   = 0;
int highThreshold  = 0;
int max            = 0;


PersonDetector::PersonDetector(int pin)
{
	pinMode(SENSOR_PIN, INPUT);
}

void PersonDetector::calibrate(int addedHeatOfPerson)
{
	// Currently hardcoded...
	min = 90;
	max = addedHeatOfPerson;

	int diff = max - min;

	lowThreshold = min + (diff / 4);
	highThreshold = max - (diff / 4);


	// print out values for debugging
	Serial.println("Calibrations:");
	Serial.println("min: ");
	Serial.println(min);
	Serial.println("lowThreshold: ");
	Serial.println(lowThreshold);
	Serial.println("highThreshold: ");
	Serial.println(highThreshold);
	Serial.println("Max: ");
	Serial.println(max);
}

bool PersonDetector::isPersonPresent()
{
	Serial.println("Returning false");
	return false;
}

