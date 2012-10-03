/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "ColorDetector.h"
#include "RGB.h"

int dataPin;
int rangePin;
int gatePin;
int ckPin;
int flashPin;

int gateSensitivity;

int colorArray[12][3];
int red;
int green;
int blue;
RGB colorObject = { 10 , 0 , 10 };

ColorDetector::ColorDetector(int _rangePin, int _gatePin, int _ck, int _dataPin, int _flashPin)
{
	dataPin = _dataPin;
	rangePin = _rangePin;
	gatePin = _gatePin;
	ckPin = _ck;
	flashPin = _flashPin;

	//default sensitivity
	digitalWrite(gatePin, LOW);

	pinMode(dataPin, INPUT);
	pinMode(rangePin, OUTPUT);
	pinMode(gatePin, OUTPUT);
}

void setSensitivity(int sense)
{
	gateSensitivity = sense;
}


RGB ColorDetector::getColor()
{
	//Run sequence required by Sensor

	//Operating sequence 1 - preperation
	digitalWrite (flashPin, HIGH);  //turn on illuminating LEDs
  
	digitalWrite (gatePin, LOW);
	digitalWrite (ckPin, LOW);

	//Operating sequence 2 - set sensitivity
	digitalWrite(rangePin, LOW); // hardcoded for now
	delay(5);

	//Operating sequence 3 - integrate light
	digitalWrite(gatePin, HIGH);
	delay(100);
	digitalWrite(gatePin, LOW);
	delay(1);

		//Operating sequence 4 - data transfer
	for (int k=0; k<3; k++){  //loop through Red, Green, Blue color
		 for (int i=0; i<12; i++){  //loop through data bits, LSB first
			 // read the input pin:
			digitalWrite(ckPin, HIGH);  //clock rising edge (data change at rising edge)
			delay(1);     //clock high state

			colorArray[i][k] = digitalRead(dataPin);  //read bit from sensor
			//colorArray[i][k] = bitRead(analogRead(1),0);  //read LSB bit from analog input as random data for testing purposes
			
			digitalWrite(ckPin, LOW); //clock falling edge
			delay(1);        //clock low state
		}

		digitalWrite (ckPin, LOW); //hold time t2 - datasheet
		delay (1);    //hold time t2 - datasheet
	 }

	digitalWrite (flashPin, LOW);  //turn off illuminating LEDs


	  //collect bits from array to ints for each color
	for (int i=0; i<12; i++){
		bitWrite(red, i, colorArray[i][0]);
		colorObject.r = red;

		bitWrite(green, i, colorArray[i][1]);
		colorObject.g = green;

		bitWrite(blue, i, colorArray[i][2]);
		colorObject.b = blue;
	}

	//Return red, green, blue values parsed in an RGB object
	return colorObject;
}

