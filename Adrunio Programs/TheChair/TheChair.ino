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
int LEDArray[] = {9,10,11}; // Red, Green, Blue pins used on Arduino Board
LED LED1(LEDArray);
byte newColor[3] = {0,0,0};  //In RGB
byte referenceColor[3] = {0,0,0};  //In RGB

// Target color components (holds R,G,B values the target color consists of)
int __red;
int __green;
int __blue;

// Light intensity (how close are we to the target color)
//double intensity = 0.0;
int intensity;
int maxBrightness = 100;  //Measured in percentages
int brightnessChange = 10;
int colorChangeDelay = 40;

// Is there and was there a person in the chair?
boolean isPerson = false;
boolean wasPerson = false;

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
   wasPerson = isPerson;  //wasPerson will hold the previous isPerson value
   isPerson = detector.isPersonPresent();
   Serial_printf("Value: %d\n", isPerson);
   
   
   
   if(isPerson == true && wasPerson == false) //A new person sits down
   {
     // If person detected and wasn't there before, take color reading (do colorspace calculations, etc)     
     rgbObject = colorDetector.getColor();
     __red = rgbObject.r   / 16;
     __green = rgbObject.g / 16;
     __blue = rgbObject.b  / 16;
    
     Serial_printf("Target color value = %d - %d - %d\n", __red, __green, __blue);
     
     //This color should be used as reference for the loop
     referenceColor[0] = __red;
     referenceColor[1] = __green;
     referenceColor[2] = __blue;
     
     //Convert referenceColor to HSB with brightness and saturation set to very low intensity, this will be the newColor that is set as initialization
     /*
     newColor[0] = ;
     newColor[1] = ;
     newColor[2] = ;
     */
     
     //Hardcoded red
     newColor[0] = 190;
     newColor[1] = 40;
     newColor[2] = 50;
     
     //After calculations set the color of the chair to the new color
     LED1.set_Color(LEDArray, newColor);
     delay(colorChangeDelay);
   }
   else if(isPerson == true && wasPerson == true)  //Person still sitting there
   {
     // Increment brightness
     //LED1.set_Color(LEDArray, newColor);
     //change intermediate color variable by convert to HSB and add standard brightnessvalue
     if(newColor[1] < 255)
     {
       newColor[1] = newColor[1] + 1;
     }
     delay(colorChangeDelay);
     
   }else if (isPerson == false && wasPerson == true)
   {
     // If person no longer sitting, decrement brightness after delay
     // Delay could be added here
     
     //Fade out color
     for(int i=0; i<3; i++)
     {
       if(newColor[i] > 0)
       {
         newColor[i] = newColor[i] - 1;
       }
     }
     //Chnange intermediate color variable
     delay(colorChangeDelay);
   }
   delay(250);
}

