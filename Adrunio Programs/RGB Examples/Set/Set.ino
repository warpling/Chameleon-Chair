#include <LED.h>

int LEDArray[] = {12,11,10}; // Red, Green, Blue
LED LED1(LEDArray);

void setup() {
}

void loop() {
  byte red[] = {0, 255, 255};
  byte green[] = {255, 0, 255};
  byte blue[] = {255, 255, 0};

  
  // Blink
  LED1.set_Color(LEDArray, red); 
  delay(5000);
  LED1.set_Color(LEDArray, green);
  delay(5000);
  LED1.set_Color(LEDArray, blue);
  delay(5000);

}
