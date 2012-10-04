/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "PersonDetector.h"

byte SENSOR_PIN; // Will hold analog thermistor pin
int min            = 0;
int lowThreshold   = 0;
int highThreshold  = 0;
int max            = 0;

int sensorValue;


PersonDetector::PersonDetector(byte _tempSensorPin)
{
	SENSOR_PIN = _tempSensorPin;
    pinMode(SENSOR_PIN, INPUT);
}

byte PersonDetector::getThermistorPin()
{
	return SENSOR_PIN;
}

void PersonDetector::calibrate(int addedHeatOfPerson)
{
    
    // Calibration of min ---------------------------

    Serial.print("Calibrating");

    // calibrate room temperature during the first three seconds 
    while (millis() < 3000) {
      
      sensorValue = analogRead(SENSOR_PIN);
     
      // record the highest sensor value at room temp
      if (sensorValue > min)
        min = sensorValue;

      
      // Flash the LED so we know it's calibrating
      if((millis() % 1000) == 0)
        Serial.print(".");
    }

    Serial.println();

    // Calculation of max and thresholds ---------------------------

    max = min + addedHeatOfPerson;

    int diff = max - min;

    lowThreshold = min + (diff / 4);
    highThreshold = max - (diff / 4);

    // Debug printing ---------------------------

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
    int sensorValue = analogRead(SENSOR_PIN);
    return (sensorValue > lowThreshold);
}

