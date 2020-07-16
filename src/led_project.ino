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

//==========Libraries==========

#include <Arduino.h>

//==========Inputs==========

// 3-way switch variables/values
// -Pins
const int switchPin_PosA = A4;
const int switchPin_PosB = A3;
// -Pin values
int switchPin_PosA_Val = 0;
int switchPin_PosB_Val = 0;

// Delay rate variables/values for 10kOhm potentiometer
// -Pins
const int potPinDelay = A0;
// -Pin values
int potPinDelay_Val = 0;
// -Other
unsigned long delayRate_Val = 0;

// Dimmer variables/values for 10kOhm potentiometer
// -Pins
const int potPinDimmer = A1;
// -Pin values
int potPinDimmer_Val = 0;

// Pattern selection variables/values for 10kOhm potentiometer
// -Pins
const int potPinSelect = A2;
// -Pin values
int potPinSelect_Val = 0;
// -Other
int select_Val = 0;

//==========Outputs==========

// Dimmer variables/values for MOSFET
// -Pins
const int dimmerPin = 6;
// -Pin values
int dimmer_Val = 0;

// Solid colour LED variables/values
// Left/Right position based on center tri-colour LED
// -Pins
const int ledPinL[4] = {5, 4, 3, 2};
const int ledPinR[4] = {7, 8, 12, 13};
// -Pin values
int ledPinL_Val[4] = {LOW, LOW, LOW, LOW};
int ledPinR_Val[4] = {LOW, LOW, LOW, LOW};
// -Other
const int ledCount = 4;

// Center tri-colour LED variables/values
// -Pins
const int ledPinCRed = 9;
const int ledPinCBlue = 10;
const int ledPinCGreen = 11;
// -Pin values
int ledPinCRed_Val = LOW;
int ledPinCBlue_Val = LOW;
int ledPinCGreen_Val = LOW;

//==========Other==========

// EMA smoothing variables/values
// -Global variables required to remember previous loop values
// --Dimmer potentiometer
int sampleAverage_Dimmer = 0;
float sampleRate_Dimmer = 0.6;
// --Select potentiometer
int sampleAverage_Select = 0;
float sampleRate_Select = 0.6;
// --Variable delay input potentiometer
int sampleAverage_Delay = 0;
float sampleRate_Delay = 0.6;
// ---Variables used for delay in all pattern/transition functions after EMA smoothing calculations
unsigned long delay_Val_AVG;

// Pattern reset variables/values
boolean patternReset[3] = {true, true, true};

// Delay variables/values
// -Global variables required to remember previous loop values
unsigned long previousMillis_Delay = 0;
unsigned long previousMillis_Print = 0;
unsigned long previousMillis_Dimmer = 0;
unsigned long previousMillis_Select = 0;
unsigned long previousMillis_Pattern = 0;
unsigned long previousMillis_PatternRand = 0;
// -Constant value used by all transition#() functions
int tDelay = 200;

//-------------------- Setup --------------------
void setup()
{

  // Communication setup
  Serial.begin(9600);

  // LED pin setup
  // -Left/Right solid colour LED sets
  for (int i = 0; i < ledCount; i++)
  {
    pinMode(ledPinL[i], OUTPUT);
    pinMode(ledPinR[i], OUTPUT);
  }
  // -Center tri-colour LED
  pinMode(ledPinCRed, OUTPUT);
  pinMode(ledPinCBlue, OUTPUT);
  pinMode(ledPinCGreen, OUTPUT);

  // Dimmer output pin setup
  pinMode(dimmerPin, OUTPUT);

  // EMA Smoothing setup
  sampleAverage_Delay = analogRead(potPinDelay);
  sampleAverage_Dimmer = analogRead(potPinDimmer);
  sampleAverage_Select = analogRead(potPinSelect);

  // Random seed setup
  randomSeed(analogRead(A5));

  // Final Initialization
  delay(1000);
} // END: setup

//-------------------- Loop --------------------
void loop()
{

  switchAB();
  dimmer();
} // END: loop
