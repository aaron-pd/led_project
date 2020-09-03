// _____Variables Legend_____
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
// _____Notes_____
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

// Switch pins variables/values
const int pinI_switch_PosA = A3;
const int pinI_switch_PosB = A4;

// Dimmer pins variables/values for 10kOhm potentiometer
const int pinI_pot_Dimmer = A1;

// Delay rate pins variables/values for 10kOhm potentiometer
const int pinI_pot_Delay = A0;
// -Mapped variables/values
// --Unsigned long to compare with millis()
unsigned long Delay_MapVal = 0;

// Pattern selection pins variables/values for 10kOhm potentiometer
const int pinI_pot_Select = A2;

//==========Outputs==========

// Dimmer pins variables/values for MOSFET
const int pinO_Dimmer = 6;

// Solid colour LED pins variables/values
// -Left/Right position based on center tri-colour LED
const int pinO_led_L[4] = {5, 4, 3, 2};
const int pinO_led_R[4] = {7, 8, 12, 13};
// -Array count variables
// --Used when including both L and R arrays
const int led_LR_Count = 4;

// Center tri-colour LED pins variables/values
const int pinO_led_C_Red = 9;
const int pinO_led_C_Blu = 10;
const int pinO_led_C_Grn = 11;

//==========Other==========

// Reset key variables/values
// -Pattern sequence
// --Values set by reset()
boolean sequence_Key;
// -Pattern reset
// --Values set by reset()
boolean reset_Key[patternSize];

// Delay variables/values
// -Variable used by all pattern() functions
// --Initial value to avoid delayed start up
int pattern_Delay = 250;
// -Variable used by all transition() functions
// --Initial value to avoid delayed start up
int transition_Delay = 250;

//-------------------- Setup --------------------
void setup()
{

    // Communication setup
    Serial.begin(9600);

    // LED output pin setup
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
} // END: loop()