#include <ColorDetector.h>

int LEDflash = 13;
int Range = 6;
int Gate = 7;
int CK = 8;
int DataIn = 3;

int _red;
int _green;
int _blue;



//Create color detector and pass pinconfig
ColorDetector colorDetector(Range, Gate, CK, DataIn, LEDflash);  

void setup()
{
  Serial.begin(9600);
}


void loop()
{
  Serial.println("RED:");
  Serial.println(colorDetector.getColor().r);
  Serial.println("GREEN:");
  Serial.println(colorDetector.getColor().g);
  Serial.println("BLUE:");
  Serial.println(colorDetector.getColor().b);
  Serial.println("-----------------------");
  delay(200);
}
