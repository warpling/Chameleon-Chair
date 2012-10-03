/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#ifndef ColorDetector_h
#define ColorDetector_h

#include "Arduino.h"
#include "RGB.h"

class ColorDetector
{
  public:
    ColorDetector(int _rangePin, int _gatePin, int _ck, int _dataPin, int _flashPin);
	void setSensitivity(int sense);
	RGB getColor();
  private:
    int _pin;
};

#endif

