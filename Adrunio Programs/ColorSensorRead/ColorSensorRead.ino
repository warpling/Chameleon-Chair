//ColorSensorRead
//Reads data from Hamatsu Digital color sensor S9706 - 3x12bit RGB information

int ColorArray[12][3];  //columns: O-Red, 1-Green, 2-Blue  Rows: 0-LSB..11-MSB
int Red = 0;
int Green = 0;
int Blue = 0;

int LEDflash = 13;

int Range = 6;
int Gate = 7;
int CK = 8;
int DataIn = 9;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);


  pinMode(DataIn, INPUT);
  pinMode(Range, OUTPUT);
  pinMode(Gate, OUTPUT);
  pinMode(DataIn, OUTPUT);


}

// the loop routine runs over and over again forever:
void loop() {

  //Operating sequence 1 - preparation
  digitalWrite (LEDflash, HIGH);  //turn on illuminating LEDs
  digitalWrite (Gate, LOW);
  digitalWrite (CK, LOW);

  //Operating sequence 2 - set sensitivity
  digitalWrite (Range, LOW);  //set senitivity: LOW = low sensitivity
  delay (5);    //hold time t4  - datasheet

  //Operating sequence 3 - integrate light
  digitalWrite (Gate, HIGH);
  delay (100);      //light integration time
  digitalWrite (Gate, LOW);
  delay (1);  //hold time t1 - datasheet

  //Operating sequence 4 - data transfer

  for (int k=0; k<3; k++){  //loop through Red, Green, Blue color
    for (int i=0; i<12; i++){  //loop through data bits, LSB first
      // read the input pin:
      digitalWrite(CK, HIGH);  //clock rising edge (data change at rising edge)
      delay(1);     //clock high state

      ColorArray[i][k] = digitalRead(DataIn);  //read bit from sensor
      //    ColorArray[i][k] = bitRead(analogRead(1),0);  //read LSB bit from analog input as random data for testing purpouses
      digitalWrite(CK, LOW); //clock falling edge
      delay(1);        //clock low state
    }

    digitalWrite (CK, LOW); //hold time t2 - datasheet
    delay (1);    //hold time t2 - datasheet
  }

  digitalWrite (LEDflash, LOW);  //turn off illuminating LEDs


  //collect bits from array to ints for each color
  for (int i=0; i<12; i++){
    bitWrite(Red, i, ColorArray[i][0]);
    bitWrite(Green, i, ColorArray[i][1]);
    bitWrite(Blue, i, ColorArray[i][2]);
  } 


  //print array data
  for (int i=0; i<12; i++){  //loop through data bits
    for (int k=0; k<2; k++){  //loop through Red, Green, Blue color

        Serial.print(ColorArray[i][k]);
      Serial.print("  ");
    }
    Serial.println(ColorArray[i][2]);
  }

  Serial.println("");  //spacer

  //print out the results
  Serial.print("Red: ");
  Serial.println(Red);
  Serial.print("Green: ");
  Serial.println(Green);
  Serial.print("Blue: ");
  Serial.println(Blue);


  //print color data array in binary
  Serial.println("");  //spacer

  Serial.print("Red_BIN: ");
  Serial.println(Red, BIN);
  Serial.print("Green_BIN: ");
  Serial.println(Green, BIN);
  Serial.print("Blue_BIN: ");
  Serial.println(Blue, BIN);

  Serial.println("");  //spacer
  Serial.println("--------------------");  //spacer
  Serial.println("");  //spacer


  delay(10000);        // delay in between reads

}







