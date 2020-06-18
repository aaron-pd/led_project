//-------------------- Variables --------------------
//
//  Variable Shorthand Legend
//  R               - Right
//  L               - Left
//  C               - Center
//  pot             - Potentiometer
//  pin             - Input/Output board pin
//  PosA            - Position A
//  PosB            - Position B
//  Val             - Value
//  EMA             - *Exponential Moving Average (for analog input smoothing)
//
//  Code Tags
//  /////REVIEW     - May require changes; see related comments near tag
//  /////UNUSED     - Variable set up but not used
//  /////TEMPORARY  - To be removed or changed
//
// -------------------- Additional Notes --------------------
// *Exponential Moving Average (EMA) information:
// EMA sampleRate value can be adjusted between 0.1 (slow;more samples) to
// 0.9 (fast;less samples)
// See following website for information:
// https://www.norwegiancreations.com/2015/10/tutorial-potentiometers-with-arduino-and-filtering/

//==========Libraries==========

#include <Arduino.h>
#include <ledPatterns.h>

// Library variables
// -ledPatterns.h
ledPatterns ledPatterns;

//==========Inputs==========

// 3-way switch variables/values
// -Pins
// --Inputs
const int switchPin_PosA = A4;
const int switchPin_PosB = A3;
// -Pin values
// --Inputs
int switchPin_PosA_Val = 0;
int switchPin_PosB_Val = 0;

// Delay rate variables/values for 10kOhm potentiometer
// -Pins
// --Inputs
const int potPinDelay = A0;
// -Pin values
// --Inputs
int potPinDelay_Val = 0;
// --Outputs
unsigned long delayRate_Val = 0;

// Dimmer variables/values for 10kOhm potentiometer and MOSFET
// -Pins
// --Inputs
const int potPinDimmer = A1;
// --Outputs
const int dimmerPin = 6;
// -Pin values
// --Inputs
int potPinDimmer_Val = 0;
// --Outputs
int dimmer_Val = 0;

// Pattern selection variables/values for 10kOhm potentiometer
// -Pins
// --Inputs
const int potPinSelect = A2;
// -Pin values
// --Inputs
int potPinSelect_Val = 0;
// -Other
int select_Val = 0;

//==========Other==========

// EMA smoothing variables/values
// -Global variables required to remember previous loop values
// --Dimmer potentiometer
int sampleAverage_Dimmer = 0;
float sampleRate_Dimmer = 0.6;
// --Select potentiometer
int sampleAverage_Select = 0;
float sampleRate_Select = 0.6;

// Pattern reset variables/values
boolean patternReset[3] = {true, true, true};
int patternResetCount = 3;

// Delay variables/values
// -Global variables required to remember previous loop values
unsigned long previousMillis_Print = 0;
unsigned long previousMillis_Dimmer = 0;
unsigned long previousMillis_Select = 0;

//-------------------- Setup --------------------
void setup()
{

  // Communication setup
  Serial.begin(9600);

  // Dimmer output pin setup
  pinMode(dimmerPin, OUTPUT);

  // -EMA Smoothing setup
  sampleAverage_Dimmer = analogRead(potPinDimmer);
  sampleAverage_Select = analogRead(potPinSelect);

  // Random seed setup for ledPatterns.h
  // -Unused analog input pin
  ledPatterns.seedPin = A5;

  // Final Initialization
  delay(1000);
}

//-------------------- Loop --------------------
void loop()
{

  ledSwitch();
  ledDimmer();
}
