#include <Saturator.h>
#include <Printf.h>

Saturator saturator = Saturator();

void setup() {
  Serial.begin(9600);
  
  rgb_color testColor = {50, 100, 200};
  rgb_color newColor = saturator.saturate(testColor.r, testColor.g, testColor.b);
  Serial_printf("[%d, %d, %d]\n", newColor.r, newColor.g, newColor.b);
}

void loop() {
  
}

