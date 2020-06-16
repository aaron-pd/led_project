/******************************************************************
 Created with thingerbits Academy for Arduino - 16.03.2020 23:29:38
 Project     : 9 LED Pattern
 Author      : Hasarinda Manjula
 Description : Arduino PIN d3 to D12
******************************************************************/
/*
int t = 40;
int rnd =5;
int pat1t =75;

void setup()
{
   for(int i=3; i<=12; i++)
   pinMode(i,OUTPUT);
}

void loop(){

   for(int i=0; i<=rnd; i++) {
   pat1();}
   for(int i=0; i<=rnd; i++){
   pat2();}
   for(int i=0; i<=rnd; i++) {
   pat3();}
   for(int i=0; i<=rnd; i++) {
   pat4();}
   for(int i=0; i<=rnd; i++){
   pat5();}
   for(int i=0; i<=rnd; i++) {
   pat6();}
   for(int i=0; i<=rnd; i++) {
   pat7();}
   for(int i=0; i<=rnd; i++) {
   pat8();}
   for(int i=0; i<=rnd; i++) {
   pat9();}


}

void pat1(){
    for(int i=3; i<=12; i++) {
      digitalWrite(i,HIGH);
      delay(pat1t);
      digitalWrite(i,LOW);

    }

    for(int i=11; i>=4; i--) {
      digitalWrite(i,HIGH);
      delay(pat1t);
      digitalWrite(i,LOW);
    }
}
void pat2(){
     for(int i=3; i<=12; i++) {
      digitalWrite(i,HIGH);
      digitalWrite(i-1,HIGH);
      digitalWrite(i+1,HIGH);
      delay(100);
      digitalWrite(i,LOW);
      digitalWrite(i-1,LOW);
      digitalWrite(i+1,LOW);
    }

    for(int i=11; i>=4; i--) {
      digitalWrite(i,HIGH);
      digitalWrite(i-1,HIGH);
      digitalWrite(i+1,HIGH);
      delay(100);
      digitalWrite(i,LOW);
      digitalWrite(i-1,LOW);
      digitalWrite(i+1,LOW);
    }
}
void pat3(){
  for(int i=3; i<=12; i=i+2) {
      digitalWrite(i,HIGH);
      delay(100);
      digitalWrite(i,LOW);

    }

    for(int i=12; i>=3; i=i-2) {
      digitalWrite(i,HIGH);
      delay(100);
      digitalWrite(i,LOW);
    }
}
void pat4(){
      for(int i=3; i<=12; i++) {
      digitalWrite(i,HIGH);
      delay(100);
    }

    for(int i=12; i>=2; i--) {
      digitalWrite(i,HIGH);
      delay(100);
      digitalWrite(i,LOW);
    }
}
void pat5(){
     for(int i=3; i<=12; i++) {
      digitalWrite(i,HIGH);
      }
    delay(100);
    for(int i=3; i<=12; i++) {
      digitalWrite(i,LOW);
      }
    delay(100);
}
void pat6(){
       for(int i=3; i<=8; i++) {
      digitalWrite(i,HIGH);
      }
    for(int i=8; i<=12; i++) {
      digitalWrite(i,LOW);
      }
    delay(200);
    for(int i=3; i<=8; i++) {
      digitalWrite(i,LOW);
      }
    for(int i=8; i<=12; i++) {
      digitalWrite(i,HIGH);
      }
    delay(200);
}
void pat7(){
       for(int i=3; i<=12; i=i+2) {
      digitalWrite(i,HIGH);
      }
    for(int i=4; i<=12; i=i+2) {
      digitalWrite(i,LOW);
      }
    delay(200);
     for(int i=3; i<=12; i=i+2) {
      digitalWrite(i,LOW);
      }
    for(int i=4; i<=12; i=i+2) {
      digitalWrite(i,HIGH);
      }
    delay(200);
}
void pat8(){
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    delay(t);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    delay(t);
    digitalWrite(6,HIGH);
    digitalWrite(9,HIGH);
    delay(t);
    digitalWrite(6,LOW);
    digitalWrite(9,LOW);
    delay(t);
    digitalWrite(5,HIGH);
    digitalWrite(10,HIGH);
    delay(t);
    digitalWrite(5,LOW);
    digitalWrite(10,LOW);
    delay(t);
    digitalWrite(4,HIGH);
    digitalWrite(11,HIGH);
    delay(t);
    digitalWrite(4,LOW);
    digitalWrite(11,LOW);
    delay(t);
    digitalWrite(3,HIGH);
    digitalWrite(12,HIGH);
    delay(t);
    digitalWrite(3,LOW);
    digitalWrite(12,LOW);
    delay(t);
     digitalWrite(4,HIGH);
    digitalWrite(11,HIGH);
    delay(t);
    digitalWrite(4,LOW);
    digitalWrite(11,LOW);
    delay(t);
    digitalWrite(5,HIGH);
    digitalWrite(10,HIGH);
    delay(t);
    digitalWrite(5,LOW);
    digitalWrite(10,LOW);
    delay(t);
    digitalWrite(6,HIGH);
    digitalWrite(9,HIGH);
    delay(t);
    digitalWrite(6,LOW);
    digitalWrite(9,LOW);
    delay(t);
}

void pat9(){
    for(int i=3; i<=12; i++) {
      digitalWrite(i,HIGH);
    }
     for(int i=3; i<=12; i++) {
      digitalWrite(i,LOW);
      delay(100);
      digitalWrite(i,HIGH);
    }
    for(int i=11; i>=4; i--) {
      digitalWrite(i,LOW);
      delay(100);
      digitalWrite(i,HIGH);
    }

}
*/










/*
  Smoothing

  Reads repeatedly from an analog input, calculating a running average and
  printing it to the computer. Keeps ten readings in an array and continually
  averages them.

  The circuit:
  - analog sensor (potentiometer will do) attached to analog input 0

  created 22 Apr 2007
  by David A. Mellis  <dam@mellis.org>
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Smoothing
*/

// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
/*
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A0;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(average);
  delay(1);        // delay in between reads for stability
}
*/
/*
// Smoothing variables/values
int index = 0;
int average = 0;
int total = 0;

// Potentiometer input smoothing
// -Calculations
total = total - readings_Select[index];
readings_Select[index] = potPinSelect_Val;
total = total + readings_Select[index];
index = index + 1;
// -Array index reset
if (index >= readingsCount) {
  index = 0;
}
// -Average calculations
average = total / readingsCount;

// Pattern select value set by selection potentiometer with Smoothing
// calculations
select_Val = average;
select_Val = map(potPinSelect_Val, 8, 1015, 0, 999);
*/










/*
https://www.norwegiancreations.com/2015/10/tutorial-potentiometers-with-arduino-and-filtering/

//Global Variables
    int sensorPin = 0;      //pin number to use the ADC
    int sensorValue = 0;    //initialization of sensor variable, equivalent to EMA Y
    float EMA_a = 0.6;      //initialization of EMA alpha
    int EMA_S = 0;          //initialization of EMA S

void setup(){
    Serial.begin(115200);           //setup of Serial module, 115200 bits/second
    EMA_S = analogRead(sensorPin);  //set EMA S for t=1
}

void loop(){
    sensorValue = analogRead(sensorPin);                //read the sensor value using ADC
    EMA_S = (EMA_a*sensorValue) + ((1-EMA_a)*EMA_S);    //run the EMA
    Serial.println(EMA_S);                              //print digital value to serial
    delay(50);                                          //50ms delay
}
*/
/*
int sensorPin = 0; // *Made reduntant; see 'int sample Average'
int sensorValue = 0;
float sampleRate = 0.6;
int sampleAverage = 0; // *Can analogRead(sensorPin)

void setup(){
sampleAverage = analogRead(sensorPin); // *Made reduntant; see 'int sample Average'
}

void loop(){
sensorValue = analogRead(sensorPin);
sampleAverage = (sampleRate*sensorValue) + ((1-sampleRate)*sampleAverage);
sensorValue = sampleAverage
delay(50);
}
*/










/*
Example for delay library function

void ledTasks::flash(int delayTime) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(_pinOne, HIGH);
    digitalWrite(_pinTwo, HIGH);
    digitalWrite(_pinThree, HIGH);
    delay(delayTime);
    digitalWrite(_pinOne, LOW);
    digitalWrite(_pinTwo, LOW);
    digitalWrite(_pinThree, LOW);
    delay(delayTime);
  }
}
*/