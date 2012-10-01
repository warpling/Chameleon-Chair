#include <LED.h>
#include <Printf.h>
#include <PersonDetector.h>

int SpotlightArray[] = {9, 10, 11};
byte red[] = {255, 0, 0};
byte green[] = {0, 255, 0};
byte blue[] = {0, 0, 255};

boolean wasPerson = false;
byte *newColor = blue;
byte *lastColor = blue;

LED Spotlight(SpotlightArray);
PersonDetector detector(0);  //You have to pass an int. For now we pass in 0 and do nothing.

void setup()
{
  Serial.begin(9600);
  detector.calibrate(20);

  Spotlight.Fade(SpotlightArray, lastColor, newColor, 3);

}

void loop()
{
   boolean isPerson = detector.isPersonPresent();
   if(isPerson && !wasPerson) {
      newColor = red;
      Spotlight.Fade(SpotlightArray, lastColor, newColor, 3);
      lastColor = newColor;
      wasPerson = true;
   }
   else if (!isPerson && wasPerson) {
      newColor = blue;
      Spotlight.Fade(SpotlightArray, lastColor, newColor, 3);
      lastColor = newColor;
      wasPerson = false;
   }
   else {
     // Do nothing
   }
   
   delay(200);
}




