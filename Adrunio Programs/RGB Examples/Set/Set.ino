#include <LED.h>

int LEDArray[] = {12,11,10}; // Red, Green, Blue
LED LED1(LEDArray);

void setup() {
}

void loop() {
  byte red[] = {255, 0, 0};
  byte green[] = {0, 255, 0};
  byte blue[] = {0, 0, 255};

  
  // Blink
  LED1.Fade(LEDArray, red , green, 30); 
  delay(3000);
  LED1.Fade(LEDArray, green , blue, 30);
  delay(3000);
  LED1.Fade(LEDArray, blue , red, 30);
}
