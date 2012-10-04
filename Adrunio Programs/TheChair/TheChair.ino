// The Chair's main code

//Include libraries
#include <ColorDetector.h>
#include <Printf.h>
#include <PersonDetector.h>


// Globals

// Pins
// 1. ColorDetector
const int LEDflash = 13;
const int Range = 6;
const int Gate = 7;
const int CK = 8;
const int DataIn = 3;

// 2. PersonDetector
const byte tempSensorPin = A0;

// 3. LED


// Target color components (holds R,G,B values the target color consists of)
int _red;
int _green;
int _blue;

//   - light intensity
boolean isPerson;

// Setup
//   Main Calibration
//   - we should be setting all values here in constants (eg. person heat, sensitivity, pins, etc)
//   - calibrate person detection code (currently set to a three second calibration) it would
//     be good to flash the LEDs somehow to let us know not to sit on the chair at this time.
//  - calibrate any other libraries with sensitivites, pins, etc


//Create custom objects
ColorDetector colorDetector(Range, Gate, CK, DataIn, LEDflash); // Pass color detection related pins to colordetector 
PersonDetector detector(tempSensorPin);  //Pass thermistor pin to persondetector constructor

void setup()
{
  Serial.begin(9600);

}

// Loop

//
//   Check if person is detected

//   If person is sitting incremement brightness

//   Set LEDs to new target color/brightness
void loop()
{
   isPerson = detector.isPersonPresent();
   Serial_printf("Value: %d\n", isPerson);
   if(isPerson)
   {
     // If person detected and wasn't there before, take color reading (do colorspace calculations, etc)
     _red = colorDetector.getColor().r;
     _green = colorDetector.getColor().g;
     _blue = colorDetector.getColor().b;
     Serial_printf("Target color value = %d - %d - %d\n", _red, _green, _blue);
     
     //wasPerson = true;
     
   }else if (isPerson == false /*&& wasPerson == true*/)
   {
     // If person no longer sitting, decrement brightness
     
     //wasPerson = false;
   }
   delay(250);
}

