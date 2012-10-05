// The Chair's main code

//Include libraries
#include <ColorDetector.h>
#include <Printf.h>
#include <PersonDetector.h>
#include <LED.h>
#include <RGB.h>
#include <Saturator.h>

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

// 3. LEDs
int LEDArray[] = {9,10,11}; // Red, Green, Blue pins used on Arduino Board
LED LED1(LEDArray);
byte targetColor[3] = {0,0,0};  //In RGB
byte currentColor[3] = {0,0,0};  //In RGB


// Target color components (holds R,G,B values the target color consists of)
int __red;
int __green;
int __blue;

// Light intensity (how close are we to the target color)
double    intensity          = 0.0;
const int intensityIncrement = .025;
const int loopDelay          = 10;

// Is there and was there a person in the chair?
boolean isPerson  = false;
boolean wasPerson = false;

// Setup
//   Main Calibration
//   - we should be setting all values here in constants (eg. person heat, sensitivity, pins, etc)
//   - calibrate person detection code (currently set to a three second calibration) it would
//     be good to flash the LEDs somehow to let us know not to sit on the chair at this time.
//  - calibrate any other libraries with sensitivites, pins, etc


// Initalize Library objects with pinouts
ColorDetector  colorDetector(Range, Gate, CK, DataIn, LEDflash); // Pass color detection related pins to colordetector 
PersonDetector detector(tempSensorPin);                          // Pass thermistor pin to persondetector constructor
Saturator      saturator();                                      // No initialization required

void setup()
{
  Serial.begin(9600);
}

void loop()
{
   isPerson = detector.isPersonPresent(); // Check if person is detected

   if(isPerson)
      Serial_printf("Person: YES\n");
   else
      Serial_printf("Person: NO\n");
   
   if(isPerson && !wasPerson) //A new person sits down
   {
     Serial_printf("PERSON SITTING FOR FIRST TIME");
     
     // If person detected and wasn't there before, take color reading (do colorspace calculations, etc)     
     rgbObject = colorDetector.getColor();
     rgbObject.r /= 16;
     rgbObject.g /= 16;
     rgbObject.b /= 16;

    // PLAN A : HSB ADJUSTMENT
    //-----------------------------------------------------------------------------------------------
    rgbObject = saturator.saturate(rgbObject);
    //-----------------------------------------------------------------------------------------------

     
     // PLAN B : COLOR ADJUSTMENT FOR SATURATION BOOST
     //-----------------------------------------------------------------------------------------------
      /*
       // Find the biggest value and maximize it
       int maximumIndex = 0;
       int maximumValue = __red;

       if(__green > maximumValue)
         maximumIndex = 1;
       if(__blue > maximumValue)
         maximumIndex = 2;
         
       targetColor[maximumIndex] = 255;
       
       // Find the biggest value and zero it
       int minimumIndex = 0;
       int minimumValue = __red;

       if(__green < minimumValue)
         minimumIndex = 1;
       if(__blue < minimumValue)
         minimumIndex = 2;
         
       targetColor[minimumIndex] = 0;
      */  
     //-----------------------------------------------------------------------------------------------
    
     targetColor[0] = rgbObject.r;
     targetColor[1] = rgbObject.g;
     targetColor[2] = rgbObject.b;

     Serial_printf("New target color value = %d - %d - %d\n", targetColor[0], targetColor[1], targetColor[2]);     
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
  wasPerson = isPerson;  //wasPerson will hold the previous isPerson value
  delay(loopDelay);
  }


