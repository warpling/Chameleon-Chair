#include <PersonDetector.h>

PersonDetector detector(0);  //You have to pass an int. For now we pass in 0 and do nothing.

void setup()
{
  Serial.begin(96-00);
  detector.calibrate(20);
}

void loop()
{
   boolean isPerson = detector.isPersonPresent();
   Serial.println(isPerson);
   delay(250);
}




