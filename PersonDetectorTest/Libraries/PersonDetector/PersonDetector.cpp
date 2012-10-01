#include "Arduino.h"
#include "PersonDetector.h"

// Note: Here on out, 'temperature' refers to the analog input of the 
// sensor and not an actual Celcius value.

const byte SENSOR_PIN = A0; //use the thermistor @ Arduino pin Analog 0
int min            = 0;
int lowThreshold   = 0;
int highThreshold  = 0;
int max            = 0;

//<<constructor>> setup the sensor, make pin A0 an INPUT
PersonDetector::PersonDetector()
{
    pinMode(SENSOR_PIN, INPUT); //make that pin an INPUT
}

//<<destructor>>
PersonDetector::~PersonDetector(){/*nothing to destruct*/}

// calibrate for room temperature
void PersonDetector::calibrate(int addedHeatOfPerson){
	// Currently hardcoded...
	min = 90;
	max = addedHeatOfPerson;

	int diff = max - min;

	lowThreshold = min + (diff / 4);
	highThreshold = max - (diff / 4);

	// print out values for debugging
	Serial.println("Calibrations:");
	Serial.println(" * min: " + min);
	Serial.println(" * lowThreshold: " + lowThreshold);
	Serial.println(" * highThreshold: " + highThreshold);
	Serial.println(" * max: " + max);
}

// return true if we think there's a person on the seat, false otherwise
bool PersonDetector::isPersonPresent(){
	return false; // hardcoded for now
}