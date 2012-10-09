
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
const int LEDflash = 6;
const int Range    = 3;
const int Gate     = 5;
const int CK       = 4;
const int DataIn   = 2;
RGB rgbObject                 = {0, 0, 0};
rgb_color saturated_rgb_color = {0, 0, 0};

// 2. PersonDetector
const byte tempSensorPin = A0;

// 3. LEDs
int LEDArray[] = {9, 10, 11}; // Red, Green, Blue pins used on Arduino Board
LED LED1(LEDArray);
byte targetColor[3]  = {0, 0, 0};  // In inverted RGB
byte currentColor[3] = {0, 0, 0};       // In inverted RGB
byte offColor[3]     = {0, 0, 0}; // In inverted RGB

// Target color components (holds R,G,B values the target color consists of)
int __red;
int __green;
int __blue;

// Light intensity (how close are we to the target color)
double       intensity          = 0.0;
const double intensityMin       = 0.0;
const double intensityMax       = 1.0;
const double intensityIncrement = .0039;
const int    loopDelay          = 50;

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
PersonDetector detector(tempSensorPin);  // Pass thermistor pin to persondetector constructor
Saturator      sat = Saturator();        // No initialization required

void setup()
{
  Serial.begin(9600);
  LED1.set_Color(LEDArray, offColor);
  detector.calibrate(30);
  
}

void loop()
{
   //isPerson = detector.isPersonPresent(); // Check if person is detected
   isPerson = true;
   
   if(isPerson)
      Serial_printf("Person: YES\n");
   else
      Serial_printf("Person: NO\n");
   
   if(isPerson && !wasPerson) //A new person sits down
   {
     Serial_printf("\nPERSON SITTING FOR FIRST TIME\n");
     
     // If person detected and wasn't there before, take color reading (do colorspace calculations, etc)     
//     rgbObject = colorDetector.getColor();
//     rgbObject.r /= 16;
//     rgbObject.g /= 16;
//     rgbObject.b /= 16;

    // PLAN A : HSB ADJUSTMENT
    //-----------------------------------------------------------------------------------------------
    // saturated_rgb_color = sat.saturate(rgbObject.r, rgbObject.g, rgbObject.b);
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
    
    // REMOVVE
     targetColor[0] = 255;
     targetColor[1] = 0;
     targetColor[2] = 0;
    //
    
//     targetColor[0] = saturated_rgb_color.r;
//     targetColor[1] = saturated_rgb_color.g;
//     targetColor[2] = saturated_rgb_color.b;

     Serial_printf("New target color value = %d - %d - %d\n", targetColor[0], targetColor[1], targetColor[2]);     
  }
  
  intensity += isPerson ? intensityIncrement : !isPerson ? -intensityIncrement : 0;
  intensity = constrain(intensity, intensityMin, intensityMax);
  Serial.println(intensity);

  // Adjust for current light intensity
  for(int i=0; i<3; i++) {
     currentColor[i] = (intensity * intensity) * targetColor[i];
  }
  
  Serial_printf("(%d, %d, %d)\n", currentColor[0], currentColor[1], currentColor[2]);
  
  // Invert Values
//  for(int i=0; i<3; i++) {
//     currentColor[i] = 255 - currentColor[i];
//  }
    
  //After calculations set the color of the chair to the new color
//  if(intensity == 0.0)
//    LED1.set_Color(LEDArray, offColor);
//  else
    LED1.set_Color(LEDArray, currentColor);
    
  wasPerson = isPerson;  //wasPerson will hold the previous isPerson value
  
  delay(loopDelay);
  
  }


