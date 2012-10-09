#include <LED.h>

int LEDArray[] = {9,10,11}; // Red, Green, Blue
LED LED1(LEDArray);

void setup() {
}

void loop() {
   byte off[] = {0, 0, 0};
   byte red[] = {255, 0, 0};
  byte green[] = {0, 255, 0};
  byte blue[] = {0, 0, 255};

  
  // Blink
  LED1.set_Color(LEDArray, offColor);
  LED1.Fade(LEDArray, off , red, 100); 
  delay(3000);
  LED1.Fade(LEDArray, green , blue, 30);
  delay(3000);
  LED1.Fade(LEDArray, blue , red, 30);
}
