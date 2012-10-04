// The Chair's main code

//Include libraries
#include <ColorDetector.h>
#include <Printf.h>
#include <PersonDetector.h>
#include <LED.h>
#include <RGB.h>


// Globals

// Pins
// 1. ColorDetector
const int LEDflash = 13;
const int Range = 6;
const int Gate = 7;
const int CK = 8;
const int DataIn = 3;
RGB rgbObject;

// 2. PersonDetector
const byte tempSensorPin = A0;

// 3. LED
int LEDArray[] = {9,10,11}; // Red, Green, Blue
LED LED1(LEDArray);
//byte prevColor[3] = {0,0,0};
byte endColor[3] = {0,0,0};

// Target color components (holds R,G,B values the target color consists of)
int __red;
int __green;
int __blue;

// Light intensity (how close are we to the target color)
double intensity = 0.0;

// Is there and was there a person in the chair?
boolean isPerson;
boolean wasPerson;

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

void loop()
{
   //   Check if person is detected
   isPerson = detector.isPersonPresent();
   Serial_printf("Value: %d\n", isPerson);
   if(isPerson)
   {
     // If person detected and wasn't there before, take color reading (do colorspace calculations, etc)     
     rgbObject = colorDetector.getColor();
     __red = rgbObject.r   / 16;
     __green = rgbObject.g / 16;
     __blue = rgbObject.b  / 16;
    
     Serial_printf("Target color value = %d - %d - %d\n", __red, __green, __blue);
     
     //This color should be the endresult of the fade
     endColor[0] = __red;
     endColor[1] = __green;
     endColor[2] = __blue;
     
     // Next increment brightness
     if(isPerson)
       
     
     //LED1.set_Color(LEDArray, );
     
     
     //Set some historic context
     wasPerson = true;
     
   }else if (isPerson == false /*&& wasPerson == true*/)
   {
     // If person no longer sitting, decrement brightness
     delay(500);
     
     
     //wasPerson = false;
   }
   delay(250);
}

