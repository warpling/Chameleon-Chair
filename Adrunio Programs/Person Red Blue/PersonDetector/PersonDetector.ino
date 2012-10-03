#include <LED.h>
#include <Printf.h>
#include <PersonDetector.h>

int SpotlightArray[] = {12, 11, 10};
byte red[] = {0, 255, 255};
byte green[] = {255, 0, 255};
byte blue[] = {255, 255, 0};
byte off[] = {255, 255, 255};

boolean wasPerson = false;
byte *newColor = blue;
byte *lastColor = blue;

LED Spotlight(SpotlightArray);
PersonDetector detector(0);  //You have to pass an int. For now we pass in 0 and do nothing.

void setup()
{
  Serial.begin(9600);
  Spotlight.set_Color(SpotlightArray, green);
  detector.calibrate(20);
}

void loop()
{
   boolean isPerson = detector.isPersonPresent();
   if(isPerson && !wasPerson) {
      newColor = red;
      Spotlight.set_Color(SpotlightArray, blue);
      lastColor = newColor;
      wasPerson = true;
   }
   else if (!isPerson && wasPerson) {
      newColor = blue;
      Spotlight.set_Color(SpotlightArray, red);
      lastColor = newColor;
      wasPerson = false;
   }
   else {
     // Do nothing
     Spotlight.set_Color(SpotlightArray, blue);
   }
   
   delay(200);
}




