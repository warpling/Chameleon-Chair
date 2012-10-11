#include <Printf.h>
#include <LED.h>

// Serial Communication
char inData[20]; // Allocate some space for the string
char inChar = -1; // Where to store the character read
byte index  = 0; // Index into array; where to store the character

// LEDs
int LEDArray[] = {9, 10, 11}; // Red, Green, Blue
LED LEDs(LEDArray);

// Fade times
const int colorFadeTime = 30; // 3 seconds
const int offFadeTime = 50;   // 5 seconds

// Some colors
byte off[] = {0, 0, 0};
byte red[] = {255, 0, 0};
byte orangeRed[] = {255, 50, 0};
byte green[] = {0, 255, 0};
byte blue[] = {0, 0, 255};
byte purple[] = {80, 0, 200};
byte teal[] = {50, 0, 255};
byte white[] = {255, 255, 255};

// Previous and target colors
byte *previousColor;
byte *targetColor;

void setup() {
  Serial.begin(9600);
  previousColor = off;
  targetColor = off;
  
  LEDs.set_Color(LEDArray, targetColor);
}

void loop() {
  
    if (Comp("red") == 0) {
        Serial_printf("Fading to red... (%d seconds) ", (colorFadeTime/10));
        previousColor = targetColor;
        targetColor = red;
        
        LEDs.Fade(LEDArray, previousColor, targetColor, colorFadeTime); 
        Serial.println(" Done!");
    }
    else if (Comp("orangeRed") == 0) {
        Serial_printf("Fading to orange red... (%d seconds) ", (colorFadeTime/10));
        previousColor = targetColor;
        targetColor = orangeRed;
        
        LEDs.Fade(LEDArray, previousColor, targetColor, colorFadeTime); 
        Serial.println(" Done!");
    }
    else if (Comp("green") == 0) {
        Serial_printf("Fading to green... (%d seconds) ", (colorFadeTime/10));
        previousColor = targetColor;
        targetColor = green;
        
        LEDs.Fade(LEDArray, previousColor, targetColor, colorFadeTime); 
        Serial.println(" Done!");
    }
    else if (Comp("blue") == 0) {
        Serial_printf("Fading to blue... (%d seconds) ", (colorFadeTime/10));
        previousColor = targetColor;
        targetColor = blue;
        
        LEDs.Fade(LEDArray, previousColor, targetColor, colorFadeTime); 
        Serial.println(" Done!");
    }
    else if (Comp("purple") == 0) {
        Serial_printf("Fading to purple... (%d seconds) ", (colorFadeTime/10));
        previousColor = targetColor;
        targetColor = purple;
        
        LEDs.Fade(LEDArray, previousColor, targetColor, colorFadeTime); 
        Serial.println(" Done!");
    }
    else if (Comp("teal") == 0) {
        Serial_printf("Fading to teal... (%d seconds) ", (colorFadeTime/10));
        previousColor = targetColor;
        targetColor = teal;
        
        LEDs.Fade(LEDArray, previousColor, targetColor, colorFadeTime); 
        Serial.println(" Done!");
    }
    else if (Comp("off") == 0) {
        Serial_printf("Fading off... (%d seconds) ", (offFadeTime/10));
        previousColor = targetColor;
        targetColor = off;
        
        LEDs.Fade(LEDArray, previousColor, targetColor, offFadeTime);
        // Without this, the LEDs never FULLY shut off
        LEDs.set_Color(LEDArray, off);
 
        Serial.println(" Done!");
    }
    else if (Comp("white") == 0) {
        Serial_printf("Fading to white... (%d seconds) ", (colorFadeTime/10));
        previousColor = targetColor;
        targetColor = white;
        
        LEDs.Fade(LEDArray, previousColor, targetColor, colorFadeTime); 
        Serial.println(" Done!");
    }
    else {
      Comp("clear");
    }
  
//  LEDs.set_Color(LEDArray, red);
//  LEDs.Fade(LEDArray, red , green, 10); 
//  LEDs.Fade(LEDArray, green , blue, 10);
//  LEDs.Fade(LEDArray, blue , red, 10);
}

char Comp(char* This) {
  
    // Hacky magic keyword to clear read buffer if there's a problem
    if(strcmp("clear", This) == 0) {      
        if (strcmp(inData,This)  == 0) {
        for (int i=0;i<19;i++) {
            inData[i]=0;
        }
        index=0;
        
        Serial.println("Cleared read buffer.");
        return(0);
      }
    }
    
    while (Serial.available() > 0) // Don't read unless
                                   // there you know there is data
    {
        if(index < 19) // One less than the size of the array
        {
            inChar = Serial.read(); // Read a character
            inData[index] = inChar; // Store it
            index++; // Increment where to write next
            inData[index] = '\0'; // Null terminate the string
        }
    }

    if (strcmp(inData,This)  == 0) {
        for (int i=0;i<19;i++) {
            inData[i]=0;
        }
        index=0;
        return(0);
    }
    else {
        return(1);
    }
}

