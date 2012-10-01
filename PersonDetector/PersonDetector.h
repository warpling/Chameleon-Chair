/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#ifndef PersonDetector_h
#define PersonDetector_h

#include "Arduino.h"

class PersonDetector
{
  public:
    PersonDetector(int pin);
    void calibrate(int addedHeatOfPerson);
    bool isPersonPresent();
  private:
    int _pin;
};

#endif

