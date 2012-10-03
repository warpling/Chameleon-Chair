#include <LED.h>
#include <Printf.h>
#include <PersonDetector.h>

int SpotlightArray[] = {11, 10, 9};
byte red[] = {0, 255, 255};
byte green[] = {255, 0, 255};
byte blue[] = {255, 255, 0};
byte off[] = {255, 255, 255};

boolean isPerson = false;
boolean wasPerson = false;
byte *newColor = blue;
byte *lastColor = blue;

LED Spotlight(SpotlightArray);
PersonDetector detector(0);  //You have to pass an int. For now we pass in 0 and do nothing.

void setup()
{
  Serial.begin(9600);
  Spotlight.set_Color(SpotlightArray, green);
  detector.calibrate(30);
  Spotlight.set_Color(SpotlightArray, off);
}

void loop()
{
   isPerson = detector.isPersonPresent();
   
   
   // keyboard testing code
  /* 
   if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    byte incomingByte = Serial.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'a') {
      isPerson = true;
    } 
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'b') {
      isPerson = false;
    }
  }
  */
   
   if(isPerson && !wasPerson) {
      newColor = red;
      Spotlight.set_Color(SpotlightArray, newColor);
      lastColor = newColor;
      wasPerson = true;
   }
   else if (!isPerson && wasPerson) {
      newColor = blue;
      Spotlight.set_Color(SpotlightArray, newColor);
      lastColor = newColor;
      wasPerson = false;
   }
   else {
     // Do nothing
     Spotlight.set_Color(SpotlightArray, lastColor);
   }
   
   delay(400);
}




