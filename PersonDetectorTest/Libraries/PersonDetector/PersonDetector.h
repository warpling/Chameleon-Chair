#ifndef PERSONDETECTOR_H
#define PERSONDETECTOR_H

#include "Arduino.h"

class PersonDetector { 
public:
	PersonDetector();
	~PersonDetector();
	void calibrate(int addedHeatOfPerson);
    bool isPersonPresent();
};

#endif