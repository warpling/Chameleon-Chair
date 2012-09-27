#ifndef PERSONDETECTOR_H
#define PERSONDETECTOR_H

#include "WProgram.h"
#include "Arduino.h"

class PersonDetector { 
public:
	PersonDetector();
	~PersonDetector();
	void calibrate(int addedHeatOfPerson);
    void isPersonPresent();
};

#endif