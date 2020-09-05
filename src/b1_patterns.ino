//-------------------- Repeating Pattern Functions --------------------

//==========Class==========

// Base Class
class Pattern
{
public:
    // Polymorphic runtime pure virtual function declaration
    virtual void pattern(unsigned long func_Delay_Val) = 0;

protected:
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
        unsigned long ms1_Current = millis();
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
        unsigned long ms1_Current = millis();
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
        unsigned long ms1_Current = millis();
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
        unsigned long ms1_Current = millis();
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