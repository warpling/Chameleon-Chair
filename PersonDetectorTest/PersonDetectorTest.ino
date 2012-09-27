#include <PersonDetector.h>

PersonDetector detector(); // Initialize an instance of the class

void setup()
{
  detector.calibrate(40);
}

void loop()
{
  boolean isPerson = detector.isPersonPresent();
    
  Serial.println(isPerson);
  
  delay(250);
}
