/*
  LED.h - Library for LEDs.
  Created by Benjamin W�st, Januar 21, 2012.
  Released into the public domain.
*/
#ifndef LED_h
#define LED_h


  #if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
  #else
  #include "WProgram.h"
  #endif


class LED
{
  public:
    LED(int LEDArray[]);
    void Fade(int LEDArray[],byte start_color[], byte end_color[], int fade_delay);
    void set_Color (int LEDArray[], byte* rgb);
  private:
    int calculate_linear_fade_position_to_exponential(int position, double pwm_max_steps, double gamma_correction);    
};

#endif