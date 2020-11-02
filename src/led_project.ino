//-------------------- Variables Legend --------------------
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
//-------------------- Notes --------------------
//  When adding new transitions:
//  -Update 'transitionRandom()' object declarations and array
//  When adding new patterns:
//  -Update global variable 'patternSize' value
//  -Update 'select()' object declaration and array
//  -Update 'patternRandom()' object declarations and array

//-------------------- Variables/Values --------------------

//==========Libraries==========

#include <Arduino.h>

//==========Macros==========

// Macro to find the true size of an array
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))

//==========Global==========

// Total number of patterns
// -Constant required for arrays
const unsigned char patternSize = 4;

// Array count variables
// -Used when including both L and R array sets
const unsigned char led_LR_Count = 4;

// Reset key variables/values
// -Pattern sequence
// --Values set by reset()
boolean sequence_Key;
// -Pattern reset
// --Values set by reset()
boolean reset_Key[patternSize];

//==========Input Pins==========

// Switch pins variables/values
const char pinI_switch_PosA = A3;
const char pinI_switch_PosB = A4;

// Dimmer pins variables/values for 10kOhm potentiometer
const char pinI_pot_Dimmer = A1;

// Delay rate pins variables/values for 10kOhm potentiometer
const char pinI_pot_Delay = A0;

// Pattern selection pins variables/values for 10kOhm potentiometer
const char pinI_pot_Select = A2;

//==========Output Pins==========

// Dimmer pins variables/values for MOSFET
const char pinO_Dimmer = 6;

// Solid colour LED pins variables/values
// -Left/Right position based on center tri-colour LED
const char pinO_led_L[4] = {5, 4, 3, 2};
const char pinO_led_R[4] = {7, 8, 12, 13};

// Center tri-colour LED pins variables/values
const char pinO_led_C_Red = 9;
const char pinO_led_C_Blu = 10;
const char pinO_led_C_Grn = 11;

//-------------------- Main Program --------------------

//==========setup()==========

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

//==========loop()==========

void loop()
{

    dimmer();
    switch_AB();
} // END: loop()

//-------------------- Miscellaneous Functions --------------------

//==========reset()==========

// Set reset_Key[#] and sequence_Key to 'false' and all LEDs to 'LOW'
// -reset_Key[#] used in select() and patternRandom() functions
// -sequence_Key used in all pattern(#) functions
// -Usage: run reset() function then set value to 'true' for chosen array
void reset()
{

    for (unsigned int i = 0; i < sizeof(reset_Key); i++)
    {
        reset_Key[i] = false;
    }
    sequence_Key = false;
    off();
} // END: reset()

//==========on()==========

// LEDs are always on, values set to 'HIGH'
void on()
{

    digitalWrite(pinO_led_C_Red, HIGH);
    digitalWrite(pinO_led_C_Blu, HIGH);
    digitalWrite(pinO_led_C_Grn, HIGH);
    for (int i = 0; i < led_LR_Count; i++)
    {
        digitalWrite(pinO_led_L[i], HIGH);
        digitalWrite(pinO_led_R[i], HIGH);
    }
} // END: on()

//==========off()==========

// LEDs are always off, values set to 'LOW'
void off()
{
    digitalWrite(pinO_led_C_Red, LOW);
    digitalWrite(pinO_led_C_Blu, LOW);
    digitalWrite(pinO_led_C_Grn, LOW);
    for (int i = 0; i < led_LR_Count; i++)
    {
        digitalWrite(pinO_led_L[i], LOW);
        digitalWrite(pinO_led_R[i], LOW);
    }
} // END: off()

//-------------------- Transition Pattern Functions --------------------

//==========Class==========

// Base Class
class Transition
{
public:
    // Polymorphic runtime pure virtual function declaration
    virtual void transition() = 0;

protected:
    // Transition pattern sequence delay variables/values
    int transition_Delay = (patternDelay() / 2);
}; // END: class Transition

//==========Derived==========

// Derived 1 : Transition
// Transition LED pattern 0
// -Fade through LEDs outwards from the center
class Transition1 : public Transition
{
public:
    void transition()
    {

        // LED Pattern
        digitalWrite(pinO_led_L[0], HIGH);
        digitalWrite(pinO_led_R[0], HIGH);

        for (int i = 0; i < led_LR_Count; i++)
        {
            digitalWrite(pinO_led_L[i - 1], LOW);
            digitalWrite(pinO_led_R[i - 1], LOW);
            digitalWrite(pinO_led_L[i], HIGH);
            digitalWrite(pinO_led_R[i], HIGH);
            delay(transition_Delay);
        }
        digitalWrite(pinO_led_L[3], LOW);
        digitalWrite(pinO_led_R[3], LOW);
        delay(transition_Delay);
        off();
    };
}; // END: transition() : Transition1

// Derived 2 : Transition
// Transition LED pattern 1
// -Fade through LEDs outwards from the center, with one LED following
class Transition2 : public Transition
{
public:
    void transition()
    {

        // LED Pattern
        digitalWrite(pinO_led_L[0], HIGH);
        digitalWrite(pinO_led_R[0], HIGH);
        delay(transition_Delay);
        for (int i = 0; i < (led_LR_Count - 1); i++)
        {
            digitalWrite(pinO_led_L[i - 1], LOW);
            digitalWrite(pinO_led_R[i - 1], LOW);
            digitalWrite(pinO_led_L[i + 1], HIGH);
            digitalWrite(pinO_led_R[i + 1], HIGH);
            delay(transition_Delay);
        }
        digitalWrite(pinO_led_L[2], LOW);
        digitalWrite(pinO_led_R[2], LOW);
        delay(transition_Delay);
        digitalWrite(pinO_led_L[3], LOW);
        digitalWrite(pinO_led_R[3], LOW);
        delay(transition_Delay);
        off();
    };
}; // END: transition() : Transition2

// Derived 3 : Transition
// Transition LED pattern 2
// -Turn on two pairs of LEDs at a time until all LEDs are on
class Transition3 : public Transition
{
public:
    void transition()
    {

        // LED Pattern
        digitalWrite(pinO_led_L[0], HIGH);
        digitalWrite(pinO_led_L[1], HIGH);
        delay(transition_Delay);
        digitalWrite(pinO_led_R[0], HIGH);
        digitalWrite(pinO_led_R[1], HIGH);
        delay(transition_Delay);
        digitalWrite(pinO_led_L[2], HIGH);
        digitalWrite(pinO_led_L[3], HIGH);
        delay(transition_Delay);
        digitalWrite(pinO_led_R[2], HIGH);
        digitalWrite(pinO_led_R[3], HIGH);
        delay(transition_Delay);
        off();
    };
}; // END: transition() : Transition3

//-------------------- Repeating Pattern Functions --------------------

//==========Class==========

// Base Class
class Pattern
{
public:
    // Polymorphic runtime pure virtual function declaration
    virtual void pattern(unsigned long func_Delay_Val) = 0;

protected:
    // Delay variables/values
    unsigned long ms1_Current = millis();

    // Pattern sequence delay variables/values
    int pattern_Delay = (patternDelay() / 2);
}; // END: class Pattern

//==========Derived==========

// Derived 1 : Pattern
// Sets LED pattern
// -Pattern will flash all LEDs simultaneously
// -func_Delay_Val = user custom value or EMA filtered input variable 'patternDelay()'
class Pattern1 : public Pattern
{
public:
    void pattern(unsigned long func_Delay_Val)
    {

        // Delay variables/values
        static unsigned long ms1_Previous = 0;

        // Delay 1
        if (ms1_Current - ms1_Previous >= func_Delay_Val)
        {
            ms1_Previous = ms1_Current;

            // LED pattern
            if (sequence_Key == false)
            {
                on();
                sequence_Key = true;
                delay(pattern_Delay);
            }
            else
            {
                off();
                sequence_Key = false;
                delay(pattern_Delay);
            }
        }
    };
}; // END: pattern() : Pattern1

// Derived 2 : Pattern
// Sets LED pattern
// -Pattern will flash center LED, then fade through the following LEDs outwards
// -func_Delay_Val = user custom value or EMA filtered input variable 'patternDelay()'
class Pattern2 : public Pattern
{
public:
    void pattern(unsigned long func_Delay_Val)
    {

        // Delay variables/values
        static unsigned long ms1_Previous = 0;

        // Delay 1
        if (ms1_Current - ms1_Previous >= func_Delay_Val)
        {
            ms1_Previous = ms1_Current;

            // LED pattern
            if (sequence_Key == false)
            {
                digitalWrite(pinO_led_C_Red, HIGH);
                digitalWrite(pinO_led_C_Blu, HIGH);
                digitalWrite(pinO_led_C_Grn, HIGH);
                for (int i = 0; i < led_LR_Count; i++)
                {
                    digitalWrite(pinO_led_L[i], LOW);
                    digitalWrite(pinO_led_R[i], LOW);
                }
                sequence_Key = true;
                delay(pattern_Delay);
            }
            else
            {
                digitalWrite(pinO_led_C_Red, LOW);
                digitalWrite(pinO_led_C_Blu, LOW);
                digitalWrite(pinO_led_C_Grn, LOW);
                for (int i = 0; i < led_LR_Count; i++)
                {
                    digitalWrite(pinO_led_L[i], HIGH);
                    digitalWrite(pinO_led_R[i], HIGH);
                    delay(pattern_Delay);
                    digitalWrite(pinO_led_L[i], LOW);
                    digitalWrite(pinO_led_R[i], LOW);
                }
                off();
                sequence_Key = false;
                delay(pattern_Delay);
            }
        }
    };
}; // END: pattern() : Pattern2

// Derived 3 : Pattern
// Sets LED pattern
// -Pattern will flash center LED, then fade through the following LEDs outwards, the center LED colours will match the currently lit LEDs
// -func_Delay_Val = user custom value or EMA filtered input variable 'patternDelay()'
class Pattern3 : public Pattern
{
public:
    void pattern(unsigned long func_Delay_Val)
    {

        // Delay variables/values
        static unsigned long ms1_Previous = 0;

        // Delay 1
        if (ms1_Current - ms1_Previous >= func_Delay_Val)
        {
            ms1_Previous = ms1_Current;

            // LED pattern
            if (sequence_Key == false)
            {
                digitalWrite(pinO_led_C_Red, HIGH);
                digitalWrite(pinO_led_C_Blu, HIGH);
                digitalWrite(pinO_led_C_Grn, HIGH);
                sequence_Key = true;
                delay(pattern_Delay);
            }
            else
            {
                digitalWrite(pinO_led_C_Red, HIGH);
                digitalWrite(pinO_led_C_Blu, LOW);
                digitalWrite(pinO_led_C_Grn, LOW);
                digitalWrite(pinO_led_L[0], HIGH);
                digitalWrite(pinO_led_R[0], HIGH);
                delay(pattern_Delay);
                digitalWrite(pinO_led_C_Red, HIGH);
                digitalWrite(pinO_led_C_Blu, LOW);
                digitalWrite(pinO_led_C_Grn, HIGH);
                digitalWrite(pinO_led_L[0], LOW);
                digitalWrite(pinO_led_R[0], LOW);
                digitalWrite(pinO_led_L[1], HIGH);
                digitalWrite(pinO_led_R[1], HIGH);
                delay(pattern_Delay);
                digitalWrite(pinO_led_C_Red, LOW);
                digitalWrite(pinO_led_C_Blu, HIGH);
                digitalWrite(pinO_led_C_Grn, LOW);
                digitalWrite(pinO_led_L[1], LOW);
                digitalWrite(pinO_led_R[1], LOW);
                digitalWrite(pinO_led_L[2], HIGH);
                digitalWrite(pinO_led_R[2], HIGH);
                delay(pattern_Delay);
                digitalWrite(pinO_led_C_Red, LOW);
                digitalWrite(pinO_led_C_Blu, LOW);
                digitalWrite(pinO_led_C_Grn, HIGH);
                digitalWrite(pinO_led_L[2], LOW);
                digitalWrite(pinO_led_R[2], LOW);
                digitalWrite(pinO_led_L[3], HIGH);
                digitalWrite(pinO_led_R[3], HIGH);
                delay(pattern_Delay);
                off();
                sequence_Key = false;
                delay(pattern_Delay);
            }
        }
    };
}; // END: pattern() : Pattern3

// Derived 4 : Pattern
// Sets LED pattern
// -Left and Right sets of LEDs will display the same pair (colour) with matching center LED colour
// -func_Delay_Val = user custom value or EMA filtered input variable 'patternDelay()'
class Pattern4 : public Pattern
{
public:
    void pattern(unsigned long func_Delay_Val)
    {

        // Delay variables/values
        static unsigned long ms1_Previous = 0;

        // Randomizer variables/values
        int rnd_sequence;

        // Delay 1
        if (ms1_Current - ms1_Previous >= func_Delay_Val)
        {
            ms1_Previous = ms1_Current;

            // Randomizer
            rnd_sequence = random(led_LR_Count);

            // LED pattern
            if (sequence_Key == false)
            {
                // Switch/Case
                switch (rnd_sequence)
                {

                // Red
                case 0:
                {
                    digitalWrite(pinO_led_C_Red, HIGH);
                    digitalWrite(pinO_led_L[0], HIGH);
                    digitalWrite(pinO_led_R[0], HIGH);
                    sequence_Key = true;
                    delay(pattern_Delay);
                }
                break; // END: case

                // Yellow
                case 1:
                {
                    digitalWrite(pinO_led_C_Red, HIGH);
                    digitalWrite(pinO_led_C_Grn, HIGH);
                    digitalWrite(pinO_led_L[1], HIGH);
                    digitalWrite(pinO_led_R[1], HIGH);
                    sequence_Key = true;
                    delay(pattern_Delay);
                }
                break; // END: case

                // Blue
                case 2:
                {
                    digitalWrite(pinO_led_C_Blu, HIGH);
                    digitalWrite(pinO_led_L[2], HIGH);
                    digitalWrite(pinO_led_R[2], HIGH);
                    sequence_Key = true;
                    delay(pattern_Delay);
                }
                break; // END: case

                // Green
                case 3:
                {
                    digitalWrite(pinO_led_C_Grn, HIGH);
                    digitalWrite(pinO_led_L[3], HIGH);
                    digitalWrite(pinO_led_R[3], HIGH);
                    sequence_Key = true;
                    delay(pattern_Delay);
                }
                break; // END: case
                }
            } // END: if
            else
            {
                off();
                sequence_Key = false;
                delay(pattern_Delay);
            }; // END: else
        }
    };
}; // END: pattern() : Pattern4

//-------------------- Randomizer Functions --------------------

//==========transitionRandom()==========

// Randomly play a transition pattern
void transitionRandom()
{

    // Transition object declarations
    Transition1 t1;
    Transition2 t2;
    Transition3 t3;
    Transition *transition[] = {&t1, &t2, &t3};

    // Run random transition
    transition[random(ARRAYSIZE(transition))]->transition();
} // END: transitionRandom()

//==========patternRandom()==========

// Randomly play a pattern
void patternRandom()
{

    // Pattern object declarations
    Pattern1 p1;
    Pattern2 p2;
    Pattern3 p3;
    Pattern4 p4;
    Pattern *pattern[] = {&p1, &p2, &p3, &p4};

    // Delay variables/values
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = (random(4, 6) * 1000);
    static unsigned long ms1_Previous = 0;

    // Randomizer variables/values
    static unsigned char rnd;

    // Delay 1
    if (ms1_Current - ms1_Previous >= ms1_Interval)
    {
        ms1_Previous = ms1_Current;

        // Randomized pattern selection
        rnd = random(ARRAYSIZE(pattern));
    }

    // One time reset and transition pattern
    while (reset_Key[rnd] == false)
    {
        reset();
        reset_Key[rnd] = true;
        transitionRandom();
    }

    // Run pattern
    pattern[rnd]->pattern(patternDelay());
} //END: patternRandom()

//-------------------- Input Functions --------------------

//==========switch_AB()==========

// Switch between random pattern/manual pattern selection
void switch_AB()
{

    // Switch variables/values
    static char pinI_switch_PosA_Val = 0;
    static char pinI_switch_PosB_Val = 0;

    // Read switch input values
    pinI_switch_PosA_Val = digitalRead(pinI_switch_PosA);
    pinI_switch_PosB_Val = digitalRead(pinI_switch_PosB);

    // Reset key variables/values
    // -'false' declaration to avoid delayed start up
    static boolean switch_PosA_Key = false;
    static boolean switch_PosB_Key = false;

    // Switch position 'A'
    // -Play selected patterns only
    if (pinI_switch_PosA_Val == HIGH)
    {
        // One time reset
        while (switch_PosA_Key == false)
        {
            reset();
            switch_PosA_Key = true;
            switch_PosB_Key = false;
        }
        // Run selected pattern
        select();
    } // END: if

    // Switch position 'B'
    // -Play all patterns randomly
    else if (pinI_switch_PosB_Val == HIGH)
    {
        // One time reset
        while (switch_PosB_Key == false)
        {
            reset();
            switch_PosA_Key = false;
            switch_PosB_Key = true;
        }
        // Run randomized pattern
        patternRandom();
    } // END: else if

    // Turn all LEDs off if switch state is undetermined
    // -Bug avoidance
    else
    {
        reset();
        switch_PosA_Key = false;
        switch_PosB_Key = false;
    } // END: else
} // END: switch_AB()

//==========dimmer()==========

// LED dimming control determined by potentiometer value
void dimmer()
{

    // Dimmer potentiometer variables/values
    // -Pin values
    static int pinI_pot_Dimmer_Val = 0;
    // -Mapped variables/values
    static unsigned char Dimmer_MapVal = 0;

    // EMA Filtering variables/values
    static int sample_MovAvg_Dimmer = analogRead(pinI_pot_Dimmer);
    static float sample_Rate_Dimmer = 0.6;

    // Delay variables/values
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = 100;
    static unsigned long ms1_Previous = 0;

    // Delay 1
    if (ms1_Current - ms1_Previous >= ms1_Interval)
    {
        ms1_Previous = ms1_Current;

        // EMA filtering
        // -Set analog read input values
        pinI_pot_Dimmer_Val = analogRead(pinI_pot_Dimmer);
        // -Calculations
        sample_MovAvg_Dimmer = (sample_Rate_Dimmer * pinI_pot_Dimmer_Val) + ((1 - sample_Rate_Dimmer) * sample_MovAvg_Dimmer);

        // Dimmer value mapped to dimmer potentiometer value with filtering calculations
        Dimmer_MapVal = map(sample_MovAvg_Dimmer, 8, 1015, 50, 250);
    }

    // Dimness of LEDs sent to MOSFET output pin
    analogWrite(pinO_Dimmer, Dimmer_MapVal);
} // END: dimmer()

//==========patternDelay()==========

// Pattern delay potentiometer input value calculations with EMA filtering
// -Final calculated variable 'Delay_MapVal' used by transition(#) and pattern(#) functions
// -Unsigned long to compare with millis()
unsigned long patternDelay()
{

    // Delay potentiometer variables/values
    // -Pin values
    static int pinI_pot_Delay_Val = 0;
    // -Mapped variables/values
    static unsigned long Delay_MapVal = 0;

    // EMA filtering variables/values
    static int sample_MovAvg_Delay = analogRead(pinI_pot_Delay);
    static float sample_Rate_Delay = 0.6;

    // Delay variables/values
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = 100;
    static unsigned long ms1_Previous = 0;

    // Delay 1
    if (ms1_Current - ms1_Previous >= ms1_Interval)
    {
        ms1_Previous = ms1_Current;

        // EMA filtering
        // -Set analog read input values
        pinI_pot_Delay_Val = analogRead(pinI_pot_Delay);
        // -Calculations
        sample_MovAvg_Delay = (sample_Rate_Delay * pinI_pot_Delay_Val) + ((1 - sample_Rate_Delay) * sample_MovAvg_Delay);

        // Delay value mapped to delay potentiometer value with filtering calculations
        Delay_MapVal = map(sample_MovAvg_Delay, 8, 1015, 50, 250);
    }
    return Delay_MapVal;
} // END: patternDelay()

//==========select()==========

// LED pattern selection determined by potentiometer position/value
void select()
{

    // Pattern object declarations
    Pattern1 p1;
    Pattern2 p2;
    Pattern3 p3;
    Pattern4 p4;
    Pattern *pattern[] = {&p1, &p2, &p3, &p4};

    // Select potentiometer variables/values
    // -Pin values
    static int pinI_pot_Select_Val = 0;
    // -Mapped variables/values
    static unsigned char Select_MapVal = 0;

    // EMA filtering variables/values
    static int sample_MovAvg_Select = analogRead(pinI_pot_Select);
    static float sample_Rate_Select = 0.6;

    // Delay variables/values
    // -Potentiometer input EMA filtering
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = 100;
    static unsigned long ms1_Previous = 0;

    // Delay 1
    if (ms1_Current - ms1_Previous >= ms1_Interval)
    {
        ms1_Previous = ms1_Current;

        // EMA filtering
        // -Set analog read input values
        pinI_pot_Select_Val = analogRead(pinI_pot_Select);
        // -Calculations
        sample_MovAvg_Select = (sample_Rate_Select * pinI_pot_Select_Val) + ((1 - sample_Rate_Select) * sample_MovAvg_Select);

        // Pattern select value mapped to select potentiometer value with filtering calculations
        Select_MapVal = map(sample_MovAvg_Select, 8, 1015, 0, (patternSize + 2));
    }

    // Off
    if (Select_MapVal == 0)
    {
        // One time reset and LED values set to 'LOW'
        reset();
    }

    // Play selected pattern
    else if (Select_MapVal >= 1 && Select_MapVal <= patternSize)
    {
        // One time reset and transition pattern
        while (reset_Key[Select_MapVal - 1] == false)
        {
            reset();
            reset_Key[Select_MapVal - 1] = true;
        }
        // Run pattern
        pattern[Select_MapVal - 1]->pattern(patternDelay());
    }

    // On
    else
    {
        // One time reset and LED values set to 'HIGH'
        reset();
        on();
    }
} // END: select()