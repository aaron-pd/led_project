//  _____Variables Legend_____
//
// --Devices--
//  R               - Right
//  L               - Left
//  C               - Center
//  led             - LED lights
//  pot             - Potentiometer
//  switch          - Two position switch
//
// --Functions--
//  Delay           - User adjustable interval delay for patterns
//  Dimmer          - User adjustable brightness control
//  Select          - User manual pattern selection
//  pattern         - Continuously looping pattern
//  transition      - One time pattern
//
// --Exponential Moving Average/Input Filtering--
//  rate            - Rate at which moving average is calculated
//  sample          - EMA exclusive variables/values
//  MovAvg          - Moving Average (analog input filtering moving average value)
//
// --Miscellaneous--
//  pinI            - Input board pin
//  pinO            - Output board pin
//  PosA            - Position A
//  PosB            - Position B
//  ms#             - Millisecond delay variables comparing against millis()
//  rnd             - Random
//  func            - Function specific variables taking incoming global variables
//  sequence        - Pattern sequence order
//  Key             - Boolean variables used to run a function once followed by disabling itself
//  Val             - Value
//  MapVal          - Values mapped to potentiometer values (after EMA input filtering calculations)
//
//_____Notes_____
//  -When adding new transitions:
//   -Update transitionRandom() object declarations and array
//  -When adding new patterns:
//   -Update global variable patternSize value
//   -Update patternRandom() object declarations and array
//   -Update select() object declaration and array

//-------------------- Variables/Values --------------------

//==========Libraries==========

#include <Arduino.h>

//==========Defines==========

// Macro to find the true size of an array
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))

//==========Pattern Constants==========
// Total number of patterns
// -Constant required for arrays
const int patternSize = 4;

//==========Inputs==========

// Switch variables/values
// -Pins
const int pinI_switch_PosA = A3;
const int pinI_switch_PosB = A4;
// -Pin values
int pinI_switch_PosA_Val = 0;
int pinI_switch_PosB_Val = 0;

// Delay rate variables/values for 10kOhm potentiometer
// -Pins
const int pinI_pot_Delay = A0;
// -Pin values
int pinI_pot_Delay_Val = 0;
// -Mapped variables/values
// --Unsigned long to compare with millis()
unsigned long Delay_MapVal = 0;

// Dimmer variables/values for 10kOhm potentiometer
// -Pins
const int pinI_pot_Dimmer = A1;
// -Pin values
int pinI_pot_Dimmer_Val = 0;
// -Mapped variables/values
int Dimmer_MapVal = 0;

// Pattern selection variables/values for 10kOhm potentiometer
// -Pins
const int pinI_pot_Select = A2;
// -Pin values
int pinI_pot_Select_Val = 0;
// -Mapped variables/values
int Select_MapVal = 0;

//==========Outputs==========

// Dimmer variables/values for MOSFET
// -Pins
const int pinO_Dimmer = 6;

// Solid colour LED variables/values
// Left/Right position based on center tri-colour LED
// -Pins
// --Separated arrays
const int pinO_led_L[4] = {5, 4, 3, 2};
const int pinO_led_R[4] = {7, 8, 12, 13};
// --Combined arrays
const int pinO_led_LR[8] = {5, 4, 3, 2, 7, 8, 12, 13};
// -Array count variables
// --Used when including both L and R arrays
const int led_LR_Count = 4;

// Center tri-colour LED variables/values
// -Pins
const int pinO_led_C_Red = 9;
const int pinO_led_C_Blu = 10;
const int pinO_led_C_Grn = 11;

//==========Other==========

// EMA filtering variables/values
// -EMA sample_Rate value can be adjusted between 0.1 (slow;higher quality) to 0.9 (fast;lower quality)
// -Global variables required to remember previous loop values
// --Dimmer potentiometer
int sample_MovAvg_Dimmer = 0;
float sample_Rate_Dimmer = 0.6;
// --Select potentiometer
int sample_MovAvg_Select = 0;
float sample_Rate_Select = 0.6;
// --Variable delay input potentiometer
int sample_MovAvg_Delay = 0;
float sample_Rate_Delay = 0.6;

// Reset key variables/values
// -Switch
// --'false' declaration to avoid delayed start up
boolean switch_PosA_Key = false;
boolean switch_PosB_Key = false;
// -Pattern sequence
// --Values set by reset()
boolean sequence_Key;
// -Pattern reset
// --Values set by reset()
boolean reset_Key[patternSize];

// Delay variables/values
// -Global variables required to remember previous loop values
// --Unsigned long to compare with millis()
// --serialPrint()
unsigned long ms1_Previous_Print = 0;
// --patternDelay()
unsigned long ms1_Previous_Delay = 0;
// --dimmer()
unsigned long ms1_Previous_Dimmer = 0;
// --select()
unsigned long ms1_Previous_Select = 0;
unsigned long ms2_Previous_SelectRun = 0;
// --pattern#()
unsigned long ms1_Previous_Pattern = 0;
// --patternRandom()
unsigned long ms1_Previous_PatternRnd = 0;
// -Variable used by all pattern() functions
// --Initial value to avoid delayed start up
int pattern_Delay = 250;
// -Variable used by all transition() functions
// --Initial value to avoid delayed start up
int transition_Delay = 250;

// Function variables/values
// -patternRandom()
// --Global variables required to remember previous loop values
int rnd_Pattern;

//-------------------- Setup --------------------
void setup()
{

    // Communication setup
    Serial.begin(9600);

    // LED pin setup
    // -Left/Right solid colour LED sets
    for (int i = 0; i < led_LR_Count; i++)
    {
        pinMode(pinO_led_L[i], OUTPUT);
        pinMode(pinO_led_R[i], OUTPUT);
    }
    // -Center tri-colour LED
    pinMode(pinO_led_C_Red, OUTPUT);
    pinMode(pinO_led_C_Blu, OUTPUT);
    pinMode(pinO_led_C_Grn, OUTPUT);

    // Dimmer output pin setup
    pinMode(pinO_Dimmer, OUTPUT);

    // EMA filtering setup
    sample_MovAvg_Delay = analogRead(pinI_pot_Delay);
    sample_MovAvg_Dimmer = analogRead(pinI_pot_Dimmer);
    sample_MovAvg_Select = analogRead(pinI_pot_Select);

    // Random seed setup
    randomSeed(analogRead(A5));

    // Set all LEDs to 'LOW' and Key values to 'false'
    reset();

    // Final Initialization
    delay(100);
} // END: setup()

//-------------------- Loop --------------------
void loop()
{

    dimmer();
    patternDelay();
    switch_AB();
    //serialPrint();
} // END: loop()