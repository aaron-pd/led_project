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
// *Exponential Moving Average (EMA) information:
// EMA sampleRate value can be adjusted between 0.1 (slow;more samples) to
// 0.15 (fast;less samples)
// See following website for information:
// https://www.norwegiancreations.com/2015/10/tutorial-potentiometers-with-arduino-and-filtering/

/*
  Things to do:
  -Dimmer still flickers
  -Make function/library for blink rate delay
  -Dimmer potentiometer: causes blink rate to slow at higher brightness(?)
  -Add capacitors to potentiometers(?)
  -Program switch for manual pattern selection/random pattern selection
  -Program more patterns/transitions -Program transition randomizer
  -Make and impliment pattern/transition/reset libraries
*/

//==========Inputs==========

// 3-way switch variables/values
// -Pins
const int switchPin_PosA = A4;
const int switchPin_PosB = A3; /////UNUSED
// -Pin values
int switchPin_PosA_Val = 0;
int switchPin_PosB_Val = 0; /////UNUSED

// Blink rate variables/values for 10kOhm potentiometer
// -Pins
const int potPinBlink = A0;
// -Pin values
int potPinBlink_Val = 0;
// -Other
unsigned long blinkRate_Val = 0;

// Dimmer variables/values for MOSFET and 10kOhm potentiometer
// -Pins
const int potPinDimmer = A1;
const int dimmerPin = 6;
// -Pin values
int potPinDimmer_Val = 0;
int dimmer_Val = 0;

// Pattern selection variables/values for 10kOhm potentiometer
// -Pins
const int potPinSelect = A2;
// -Pin values
int potPinSelect_Val = 0;
// -Other
int select_Val = 0;

//==========Outputs==========

// Solid colour LED variables/values
// Left/Right position based on center tri-colour LED
// -Pins
const int ledPinL[4] = {5, 4, 3, 2};
const int ledPinR[4] = {7, 8, 12, 13};
const int ledCount = 4;
// -Pin values
int ledPinL_Val[4] = {LOW, LOW, LOW, LOW};
int ledPinR_Val[4] = {LOW, LOW, LOW, LOW};

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

// Pattern reset variables/values
boolean patternReset[3] = {true, true, true};
int patternResetCount = 3;

// Pattern delay variables/values
// -Used to keep delays consistant between all LED pattern Functions
unsigned long previousMillis_Pattern = 0;

//-------------------- Setup --------------------
void setup() {

  // Communication setup
  Serial.begin(9600);

  // LED pin setup
  //  -Left & Right
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPinL[i], OUTPUT);
    pinMode(ledPinR[i], OUTPUT);
  }
  // -Center
  pinMode(ledPinCRed, OUTPUT);
  pinMode(ledPinCBlue, OUTPUT);
  pinMode(ledPinCGreen, OUTPUT);

  // Dimmer output (MOSFET) pin setup
  pinMode(dimmerPin, OUTPUT);

  // Initialization
  delay(1000);
}

//-------------------- Loop --------------------
void loop() {

  ledSwitch(); /////TEMPORARY: toggles serialPrint()
  ledDimmer();
  ledSelect();
}
