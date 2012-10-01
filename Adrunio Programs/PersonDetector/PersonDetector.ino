#include <Printf.h>
#include <PersonDetector.h>

PersonDetector detector(0);  //You have to pass an int. For now we pass in 0 and do nothing.

void setup()
{
  Serial.begin(9600);
  detector.calibrate(20);
}

void loop()
{
   boolean isPerson = detector.isPersonPresent();
   Serial_printf("Value: %d\n", isPerson);
   delay(250);
}




