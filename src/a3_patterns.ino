//-------------------- Repeating Pattern Functions --------------------

//==========Class==========

// Base Class
class Pattern
{
public:
    // Polymorphic runtime pure virtual function declaration
    virtual void pattern(unsigned long func_Delay_Val) = 0;
}; // END: class Pattern

//==========Derived==========

// Derived 1 : Pattern
// Sets LED pattern
// -Pattern will flash all LEDs simultaneously
// -func_Delay_Val = user custom value or EMA filtered input variable 'Delay_MapVal'
class Pattern1 : public Pattern
{
public:
    void pattern(unsigned long func_Delay_Val)
    {

        // Delay variables/values
        unsigned long ms1_Current = millis();

        // Delay 1
        if (ms1_Current - ms1_Previous_Pattern >= func_Delay_Val)
        {
            ms1_Previous_Pattern = ms1_Current;

            // LED pattern
            if (pinO_led_C_Red_Val == LOW && pinO_led_C_Blu_Val == LOW && pinO_led_C_Grn_Val == LOW)
            {
                on();
            }
            else
            {
                off();
            }
        }
    };
}; // END: pattern() : Pattern1

// Derived 2 : Pattern
// Sets LED pattern
// -Pattern will flash center LED, then fade through the following LEDs outwards
// -func_Delay_Val = user custom value or EMA filtered input variable 'Delay_MapVal'
class Pattern2 : public Pattern
{
public:
    void pattern(unsigned long func_Delay_Val)
    {

        // Delay variables/values
        unsigned long ms1_Current = millis();

        // Delay 1
        if (ms1_Current - ms1_Previous_Pattern >= func_Delay_Val)
        {
            ms1_Previous_Pattern = ms1_Current;

            // LED pattern
            if (pinO_led_C_Red_Val == LOW && pinO_led_C_Blu_Val == LOW && pinO_led_C_Grn_Val == LOW)
            {
                pinO_led_C_Red_Val = HIGH;
                pinO_led_C_Blu_Val = HIGH;
                pinO_led_C_Grn_Val = HIGH;
                digitalWrite(pinO_led_C_Red, pinO_led_C_Red_Val);
                digitalWrite(pinO_led_C_Blu, pinO_led_C_Blu_Val);
                digitalWrite(pinO_led_C_Grn, pinO_led_C_Grn_Val);
                for (int i = 0; i < led_LR_Count; i++)
                {
                    digitalWrite(pinO_led_L[i], LOW);
                    digitalWrite(pinO_led_R[i], LOW);
                }
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
            }
        }
    };
}; // END: pattern() : Pattern2

// Derived 3 : Pattern
// Sets LED pattern
// -Pattern will flash center LED, then fade through the following LEDs outwards, the center LED colours will match the currently lit LEDs
// -func_Delay_Val = user custom value or EMA filtered input variable 'Delay_MapVal'
class Pattern3 : public Pattern
{
public:
    void pattern(unsigned long func_Delay_Val)
    {

        // Delay variables/values
        unsigned long ms1_Current = millis();

        // Delay 1
        if (ms1_Current - ms1_Previous_Pattern >= func_Delay_Val)
        {
            ms1_Previous_Pattern = ms1_Current;

            // LED pattern
            if (pinO_led_C_Red_Val == LOW && pinO_led_C_Blu_Val == LOW && pinO_led_C_Grn_Val == LOW)
            {
                pinO_led_C_Red_Val = HIGH;
                pinO_led_C_Blu_Val = HIGH;
                pinO_led_C_Grn_Val = HIGH;
                digitalWrite(pinO_led_C_Red, pinO_led_C_Red_Val);
                digitalWrite(pinO_led_C_Blu, pinO_led_C_Blu_Val);
                digitalWrite(pinO_led_C_Grn, pinO_led_C_Grn_Val);
            }
            else
            {
                pinO_led_C_Blu_Val = LOW;
                pinO_led_C_Grn_Val = LOW;
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
                delay(pattern_Delay);
            }
        }
    };
}; // END: pattern() : Pattern3