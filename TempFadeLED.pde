/*
  AnalogReadSerial
 Reads an analog input on pin 0, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */
 
const int sensorPin = A0;
const int ledPin = 11;

 // Using a 10k Ohm resistor
int sensorValue = 0;         // the sensor value
int sensorMin = 550; // 525 (ambient room temp)
int sensorMax = 550; // 575 (Daniel's butt temp on cloth chair)


void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  Serial.println("\n--------------------\nCalibrating..."); 
  
   // calibrate during the first five seconds 
   while (millis() < 5000) {
     sensorValue = analogRead(sensorPin);
    
     // record the maximum sensor value
     if (sensorValue > sensorMax) {
       sensorMax = sensorValue;
     }
    
     // record the minimum sensor value
     if (sensorValue < sensorMin) {
       sensorMin = sensorValue;
     }
     
     if((millis()/100) % 2)
       analogWrite(ledPin, HIGH);
    else
       analogWrite(ledPin, LOW);
   }
   
   Serial.print("min [");
   Serial.print(sensorMin);
   Serial.print(", ");
   Serial.print(sensorMax);
   Serial.println("] max");
   
   Serial.println("Done calibrating! Begining run loop!");
}

void loop() {
  
  // read the sensor:
  sensorValue = analogRead(sensorPin);
  
  // Print it for debugging purposes
  Serial.println(sensorValue, DEC);

  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, 0, 255);

  // fade the LED using the calibrated value:
  analogWrite(ledPin, sensorValue);
  
  Serial.print("LED = ");
  Serial.print(sensorValue / 2.55);
  Serial.println("%");
  
}
