const int sensorPin = A0;
const int ledPin = 13;

// These min/max values are set to 1024 and 0 respectively,
//  so that when the program starts they will be calibrated to
//  room temperature. During testing we found ambient room "temp"
//  when using a 10k Ohm resistor to be about 525, and 575 when
//  someone was sitting on it.
int sensorValue = 0;
int baseline = 0; // set to a high temperature so it will be increased during calibration
const int addedHeatOfPerson = 50; // 575 (Daniel's butt temp on cloth chair) - 525 (abient room temp)
int minTemp, maxTemp;

// BEGIN smoothing initalization code ------------------------------------
/*

  Smoothing

  Reads repeatedly from an analog input, calculating a running average
  and printing it to the computer.  Keeps ten readings in an array and 
  continually averages them.

  Created 22 April 2007
  By David A. Mellis  <dam@mellis.org>
  modified 9 Apr 2012
  by Tom Igoe
  http://www.arduino.cc/en/Tutorial/Smoothing
  
  This example code is in the public domain.
  
  
*/

// Define the number of samples to keep track of.  The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int smoothedTemp = 0;                // the average

// END smoothing initalization code ------------------------------------


void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  // Initialize smoothing readings
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;  
  
  Serial.println("\n--------------------\nCalibrating..."); 
  
   // calibrate room temperature during the first three seconds 
   while (millis() < 3000) {
     
     sensorValue = analogRead(sensorPin);
    
     // record the highest sensor value at room temp
     if (sensorValue > baseline)
       baseline = sensorValue;

     
     // Flash the LED so we know it's calibrating
     if((millis()/200) % 2)
       analogWrite(ledPin, HIGH);
     else
       analogWrite(ledPin, LOW);
       
   }

   minTemp = baseline;
   maxTemp = baseline + addedHeatOfPerson;
   
   String debugString;
   debugString = "Calibrated: min [" + minTemp;
   debugString += ", " + maxTemp;
   debugString += "] max\n";
   Serial.println(debugString);
   
}

void loop() {
  
  // BEGIN smoothing code ------------------------------------
  // subtract the last reading:
  total= total - readings[index];         
  // read from the sensor:  
  readings[index] = analogRead(sensorPin); 
  // add the reading to the total:
  total= total + readings[index];       
  // advance to the next position in the array:  
  index = index + 1;                    

  // if we're at the end of the array wrap around to the beginning
  if (index >= numReadings)              
    index = 0;
                      
  // calculate the average:
  smoothedTemp = total / numReadings;   
  // END smoothing code ------------------------------------

  // Print it for debugging purposes
  Serial.println(smoothedTemp, DEC);

  // apply the calibration to the sensor reading
  sensorValue = map(smoothedTemp, minTemp, maxTemp, 0, 255);

  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, 0, 255);

  // fade the LED using the calibrated value:
  analogWrite(ledPin, sensorValue);
  
  int ledPercent = (sensorValue / 2.55);
  String debugString = "LED = " + ledPercent;
  debugString += "%";
  Serial.println(debugString);
  
  delay(1); // delay helps read the sensor more accurately
}
