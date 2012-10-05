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
byte targetColor[3] = {0,0,0};  //In RGB
byte currentColor[3] = {0,0,0};  //In RGB


// Target color components (holds R,G,B values the target color consists of)
int __red;
int __green;
int __blue;

// Light intensity (how close are we to the target color)
double intensity = 0.0;
int intensityIncrement = .05;
int loopDelay = 20;

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
   Serial_printf("Is there a person? (0 = no, 1 = yes) : %d\n", isPerson);
   
   
   //isPerson=true; //DEBUGGING STATEMENT, REMOVE AFTER USAGE

  
   
   if(isPerson && !wasPerson) //A new person sits down
   {
     Serial_printf("PERSON SITS FIRST TIME");
     // If person detected and wasn't there before, take color reading (do colorspace calculations, etc)     
     rgbObject = colorDetector.getColor();
     __red = rgbObject.r   / 16;
     __green = rgbObject.g / 16;
     __blue = rgbObject.b  / 16;

    // PLAN A : HSB ADJUSTMENT
    //-----------------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------------


     
     // PLAN B : COLOR ADJUSTMENT FOR SATURATION BOOST
     //-----------------------------------------------------------------------------------------------
       
       // Find the biggest value and maximize it
       String maximumIndex = 0;
       String maximumValue = __red;

       if(__green > maximumValue)
         maximumIndex = 1;
       if(__blue > maximumValue)
         maximumIndex = 2;
         
       newColor[maximumIndex] = 255;
       
       // Find the biggest value and zero it
       String minimumIndex = 0;
       String minimumValue = __red;

       if(__green < minimumValue)
         minimumIndex = 1;
       if(__blue < minimumValue)
         minimumIndex = 2;
         
       newColor[minimumIndex] = 0;
        
     //-----------------------------------------------------------------------------------------------
    
     Serial_printf("New target color value = %d - %d - %d\n", __red, __green, __blue);
     
     //This color should be used as reference for the loop
     targetColor[0] = __red;
     targetColor[1] = __green;
     targetColor[2] = __blue;
  }
  else if (isPerson && wasPerson) {
    intensity += intensityIncrement;
  }
  else {
    intensity -= intensityIncrement;
  }

  // Adjust for current light intensity
  for(int i=0; i<3; i++) {
     currentColor[i] = intensity * targetColor[i];
  }
    
     //After calculations set the color of the chair to the new color
     LED1.set_Color(LEDArray, currentColor);
     delay(colorChangeDelay);
   }
}

