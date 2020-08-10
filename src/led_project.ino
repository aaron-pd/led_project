//-------------------- Variables/Values --------------------
//
//  Variable Naming Legend
//
//  R               - Right
//  L               - Left
//  C               - Center
//  pot             - Potentiometer
//  pinI            - Input board pin
//  pinO            - Output board pin
//  PosA            - Position A
//  PosB            - Position B
//  func            - Function specific variables taking incoming global variables
//  Key             - Boolean variables used to run a function once followed by disabling itself
//  Val             - Value
//  MapVal          - Values mapped to potentiometer values
//  EMA             - *Exponential Moving Average (analog input filtering calculations)
//  MovAvg          - Moving Average (analog input filtering: saved values)
//  MapAvg          - Mapped Average to potentiometer values (analog input filtered value)
//
//-------------------- Additional Notes --------------------
// *Exponential Moving Average (EMA) information:
// EMA sample_Rate value can be adjusted between 0.1 (slow;higher quality) to 0.9 (fast;lower quality)

//==========Libraries==========

#include <Arduino.h>

//==========Defines==========

// Macro to find the true size of an array
// -Important for an array of objects
#define ARRAYSIZE(x)  (sizeof(x) / sizeof(x[0]))

//==========Inputs==========

// 3-way switch variables/values
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
unsigned long Delay_Val_MapAvg;

// Dimmer variables/values for 10kOhm potentiometer
// -Pins
const int pinI_pot_Dimmer = A1;
// -Pin values
int pinI_pot_Dimmer_Val = 0;
// -Mapped variables/values
int Dimmer_Val_MapVal = 0;

// Pattern selection variables/values for 10kOhm potentiometer
// -Pins
const int pinI_pot_Select = A2;
// -Pin values
int pinI_pot_Select_Val = 0;
// -Mapped variables/values
int Select_Val_MapVal = 0;

//==========Outputs==========

// Dimmer variables/values for MOSFET
// -Pins
const int pinO_Dimmer = 6;

// Solid colour LED variables/values
// Left/Right position based on center tri-colour LED
// -Pins
const int pinO_led_L[4] ={ 5, 4, 3, 2 };
const int pinO_led_R[4] ={ 7, 8, 12, 13 };
// -Pin values
int pinO_led_L_Val[4] ={ LOW, LOW, LOW, LOW };
int pinO_led_R_Val[4] ={ LOW, LOW, LOW, LOW };
// -Array count variable
// --Used when including both L and R arrays
const int led_LR_Count = 4;

// Center tri-colour LED variables/values
// -Pins
const int pinO_led_C_Red = 9;
const int pinO_led_C_Blu = 10;
const int pinO_led_C_Gre = 11;
// -Pin values
int pinO_led_C_Red_Val = LOW;
int pinO_led_C_Blu_Val = LOW;
int pinO_led_C_Gre_Val = LOW;

//==========Other==========

// EMA filtering variables/values
// -Global variables required to remember previous loop values
// --Dimmer potentiometer
float sample_Rate_Dimmer = 0.6;
int sample_Average_Dimmer = 0;
// --Select potentiometer
float sample_Rate_Select = 0.6;
int sample_Average_Select = 0;
// --Variable delay input potentiometer
float sample_Rate_Delay = 0.6;
int sample_Average_Delay = 0;

// Reset key variables/values
// -3-way switch
boolean switch_PosA_Key = true;
boolean switch_PosB_Key = true;
// -Pattern reset
boolean reset_Key[] ={ true, true, true };
// -Pattern randomizer
boolean randomizer_Key[] ={ true, true, true };

// Delay variables/values
// -Global variables required to remember previous loop values
// --Unsigned long to compare with millis()
unsigned long ms_Previous_Delay = 0;
unsigned long ms_Previous_Print = 0;
unsigned long ms_Previous_Dimmer = 0;
unsigned long ms_Previous_Select = 0;
unsigned long ms_Previous_Pattern = 0;
unsigned long ms_Previous_SelectRun = 0;
unsigned long ms_Previous_PatternRnd = 0;
unsigned long ms_Previous_PatternRndRun = 0;
// -Constant value used by all pattern#() functions
int pattern_Delay = 100;
// -Constant value used by all transition#() functions
int transition_Delay = 250;

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
    pinMode(pinO_led_C_Gre, OUTPUT);

    // Dimmer output pin setup
    pinMode(pinO_Dimmer, OUTPUT);

    // EMA filtering setup
    sample_Average_Delay = analogRead(pinI_pot_Delay);
    sample_Average_Dimmer = analogRead(pinI_pot_Dimmer);
    sample_Average_Select = analogRead(pinI_pot_Select);

    // Random seed setup
    randomSeed(analogRead(A5));

    // Final Initialization
    delay(1000);
} // END: setup()

//-------------------- Loop --------------------
void loop()
{

    dimmer();
    patternDelay();
    switch_AB();
    //serialPrint();
} // END: loop()
