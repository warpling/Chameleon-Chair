/*
  LED.cpp - Library for LEDs.
  Created by Benjamin Wüst, January 21, 2012.
  Released into the public domain.
*/

// Arduino Software Release Notes - ARDUINO 1.0 - 2011.11.30
// The WProgram.h file, which provides declarations for the Arduino API,
// has been renamed to Arduino.h. To create a library that will work in
// both Arduino 0022 and Arduino 1.0, you can use an #ifdef that checks
// for the ARDUINO constant, which was 22 and is now 100.

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "LED.h"

LED::LED(int LEDArray[])
{
	for(int i = 0; i < 3; i++){
   		pinMode(LEDArray[i], OUTPUT);   //Set the three LED pins as output
  	}
}

int LED::calculate_linear_fade_position_to_exponential(int position, double pwm_max_steps, double gamma_correction)
{
	// This function needs scientific backup!
	// http://www.wolframalpha.com/input/?i=plot+y%3Dround%28255*%28x%2F255%29^%282.2%29%29+from+x%3D0+to+255
	int out = round(pwm_max_steps * ( pow( (position/ 255.0) , gamma_correction) ));
	return out;
}


void LED::set_Color(int LEDArray[], byte* rgb)
{
	// 255 - the value because our RGB LED is common anode, this means a colour is full on when we output analogWrite(Pin, 0)
	for(int i = 0; i < 3; i++){
    		analogWrite(LEDArray[i], /*255 -*/ rgb[i]);
 	}
}


void LED::Fade(int LEDArray[],byte start_color[], byte end_color[], int fade_delay)
{

	int change_color_red = end_color[0] - start_color[0];
	int change_color_green = end_color[1] - start_color[1];
	int change_color_blue = end_color[2] - start_color[2];
	int max_change_color = max(abs(change_color_red),max(abs(change_color_green), abs(change_color_blue)));
	
	for(int i = 0 ; i < max_change_color; i++){
		byte temp_color_red = start_color[0] + ((LED::calculate_linear_fade_position_to_exponential(i, 255, 2.2)) * change_color_red / max_change_color);  
   		byte temp_color_green = start_color[1] + ((LED::calculate_linear_fade_position_to_exponential(i, 255, 2.2)) * change_color_green / max_change_color);
   		byte temp_color_blue = start_color[2] + ((LED::calculate_linear_fade_position_to_exponential(i, 255, 2.2)) * change_color_blue / max_change_color);      
		
   		byte temp_color[] = {temp_color_red, temp_color_green, temp_color_blue};
		LED::set_Color(LEDArray, temp_color);
    		delay(fade_delay); 
  	}
}
