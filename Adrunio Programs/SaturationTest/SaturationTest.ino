#include <Saturator.h>
#include <Printf.h>

Saturator saturator = Saturator();

void setup() {
  Serial.begin(9600);
  
  rgb_color testColor = {220, 255, 255};
  rgb_color newColor = saturator.saturate(testColor.r, testColor.g, testColor.b);
  Serial_printf("HSV [%d, %d, %d]\n", testColor.r, testColor.g, testColor.b);
  Serial_printf("RGB* [%d, %d, %d]\n", newColor.r, newColor.g, newColor.b);
}

void loop() {
  
}

