//-------------------- Repeating Pattern Functions --------------------

// Pattern delay calculations with EMA filtering
// -Function requires potentiometer input pin, input pin value and outside-of-function delay value
void patternDelay(int pinI_pot, int pinI_pot_Val, unsigned long Delay_Val_MAvg)
{

    // Delay variables/values
    unsigned long ms_Current = millis();
    unsigned long ms_Interval = 50;

    // Delay
    if (ms_Current - ms_Previous_Delay >= ms_Interval)
    {
        ms_Previous_Delay = ms_Current;

        // EMA filtering
        // -Set analog read input values
        pinI_pot_Val = analogRead(pinI_pot);
        // -calculations
        sample_Average_Delay = (sample_Rate_Delay * pinI_pot_Val) + ((1 - sample_Rate_Delay) * sample_Average_Delay);
        
        // Delay value set by delay potentiometer with filtering calculations
        Delay_Val_MAvg = sample_Average_Delay;
        Delay_Val_MAvg = map(pinI_pot_Val, 8, 1015, 0, 255);
        
        // Set value for global variable
        Delay_Val_Avg = Delay_Val_MAvg;
    }
} // END: patternDelay()

//==========Class==========

// Base Class
class Pattern
{
public:
    virtual void pattern(unsigned long Delay_Val);
};

//==========Derived==========

// Derived 1 : Pattern
// Sets LED pattern
// -Pattern will flash all LEDs simultaneously
// -Delay_Val = user custom value or EMA filtered input variable 'Delay_Val_Avg'
class Pattern1 : public Pattern
{
public:
    void pattern(unsigned long Delay_Val)
    {

        // Delay variables/values
        unsigned long ms_Current = millis();

        // Delay
        if (ms_Current - ms_Previous_Pattern >= Delay_Val)
        {
            ms_Previous_Pattern = ms_Current;

            // LED pattern
            if (pinO_led_C_Red_Val == LOW && pinO_led_C_Blu_Val == LOW && pinO_led_C_Gre_Val == LOW)
            {
                pinO_led_C_Red_Val = HIGH;
                pinO_led_C_Blu_Val = HIGH;
                pinO_led_C_Gre_Val = HIGH;
                for (int i = 0; i < led_LR_Count; i++)
                {
                    if (pinO_led_L_Val[i] == LOW && pinO_led_R_Val[i] == LOW)
                    {
                        pinO_led_L_Val[i] = HIGH;
                        pinO_led_R_Val[i] = HIGH;
                    }
                }
            }
            else
            {
                pinO_led_C_Red_Val = LOW;
                pinO_led_C_Blu_Val = LOW;
                pinO_led_C_Gre_Val = LOW;
                for (int i = 0; i < led_LR_Count; i++)
                {
                    if (pinO_led_L_Val[i] == HIGH && pinO_led_R_Val[i] == HIGH)
                    {
                        pinO_led_L_Val[i] = LOW;
                        pinO_led_R_Val[i] = LOW;
                    }
                }
            }
        }

        // Display LEDs based on values from previous if/else statement
        digitalWrite(pinO_led_C_Red, pinO_led_C_Red_Val);
        digitalWrite(pinO_led_C_Blu, pinO_led_C_Blu_Val);
        digitalWrite(pinO_led_C_Gre, pinO_led_C_Gre_Val);
        for (int i = 0; i < led_LR_Count; i++)
        {
            digitalWrite(pinO_led_L[i], pinO_led_L_Val[i]);
            digitalWrite(pinO_led_R[i], pinO_led_R_Val[i]);
        }
    };
}; // END: pattern() : Pattern1

// Derived 2 : Pattern
// Sets LED pattern
// -Pattern will flash center LED, then fade through the following LEDs outwards
// -Delay_Val = user custom value or EMA filtered input variable 'Delay_Val_Avg'
class Pattern2 : public Pattern
{
public:
    void pattern(unsigned long Delay_Val)
    {

        // Delay variables/values
        unsigned long ms_Current = millis();

        // Delay
        if (ms_Current - ms_Previous_Pattern >= Delay_Val)
        {
            ms_Previous_Pattern = ms_Current;

            // LED pattern
            if (pinO_led_C_Red_Val == LOW && pinO_led_C_Blu_Val == LOW && pinO_led_C_Gre_Val == LOW)
            {
                pinO_led_C_Red_Val = HIGH;
                pinO_led_C_Blu_Val = HIGH;
                pinO_led_C_Gre_Val = HIGH;
                digitalWrite(pinO_led_C_Red, pinO_led_C_Red_Val);
                digitalWrite(pinO_led_C_Blu, pinO_led_C_Blu_Val);
                digitalWrite(pinO_led_C_Gre, pinO_led_C_Gre_Val);
                for (int i = 0; i < led_LR_Count; i++)
                {
                    digitalWrite(pinO_led_L[i], LOW);
                    digitalWrite(pinO_led_R[i], LOW);
                }
            }
            else
            {
                pinO_led_C_Red_Val = LOW;
                pinO_led_C_Blu_Val = LOW;
                pinO_led_C_Gre_Val = LOW;
                digitalWrite(pinO_led_C_Red, pinO_led_C_Red_Val);
                digitalWrite(pinO_led_C_Blu, pinO_led_C_Blu_Val);
                digitalWrite(pinO_led_C_Gre, pinO_led_C_Gre_Val);
                for (int i = 0; i < led_LR_Count; i++)
                {
                    digitalWrite(pinO_led_L[i], HIGH);
                    digitalWrite(pinO_led_R[i], HIGH);
                    delay(50);
                    digitalWrite(pinO_led_L[i], LOW);
                    digitalWrite(pinO_led_R[i], LOW);
                }
            }
        }
    };
}; // END: pattern() : Pattern2

// Derived 3 : Pattern
// Sets LED pattern
// -Pattern will flash center LED, then fade through the following LEDs outwards, center LED flashes matching colours with pattern
// -Delay_Val = user custom value or EMA filtered input variable 'Delay_Val_Avg'
class Pattern3 : public Pattern
{
public:
    void pattern(unsigned long Delay_Val)
    {

        // Delay variables/values
        unsigned long ms_Current = millis();

        // Delay
        if (ms_Current - ms_Previous_Pattern >= Delay_Val)
        {
            ms_Previous_Pattern = ms_Current;

            // LED pattern
            if (pinO_led_C_Red_Val == LOW && pinO_led_C_Blu_Val == LOW && pinO_led_C_Gre_Val == LOW)
            {
                pinO_led_C_Red_Val = HIGH;
                pinO_led_C_Blu_Val = HIGH;
                pinO_led_C_Gre_Val = HIGH;
                digitalWrite(pinO_led_C_Red, pinO_led_C_Red_Val);
                digitalWrite(pinO_led_C_Blu, pinO_led_C_Blu_Val);
                digitalWrite(pinO_led_C_Gre, pinO_led_C_Gre_Val);
                for (int i = 0; i < led_LR_Count; i++)
                {
                    digitalWrite(pinO_led_L[i], LOW);
                    digitalWrite(pinO_led_R[i], LOW);
                }
            }
            else
            {
                pinO_led_C_Red_Val = LOW;
                pinO_led_C_Blu_Val = LOW;
                pinO_led_C_Gre_Val = LOW;
                digitalWrite(pinO_led_C_Red, HIGH);
                digitalWrite(pinO_led_C_Blu, LOW);
                digitalWrite(pinO_led_C_Gre, LOW);
                digitalWrite(pinO_led_L[0], HIGH);
                digitalWrite(pinO_led_R[0], HIGH);
                delay(50);
                digitalWrite(pinO_led_C_Red, HIGH);
                digitalWrite(pinO_led_C_Blu, LOW);
                digitalWrite(pinO_led_C_Gre, HIGH);
                digitalWrite(pinO_led_L[0], LOW);
                digitalWrite(pinO_led_R[0], LOW);
                digitalWrite(pinO_led_L[1], HIGH);
                digitalWrite(pinO_led_R[1], HIGH);
                delay(50);
                digitalWrite(pinO_led_C_Red, LOW);
                digitalWrite(pinO_led_C_Blu, HIGH);
                digitalWrite(pinO_led_C_Gre, LOW);
                digitalWrite(pinO_led_L[1], LOW);
                digitalWrite(pinO_led_R[1], LOW);
                digitalWrite(pinO_led_L[2], HIGH);
                digitalWrite(pinO_led_R[2], HIGH);
                delay(50);
                digitalWrite(pinO_led_C_Red, LOW);
                digitalWrite(pinO_led_C_Blu, LOW);
                digitalWrite(pinO_led_C_Gre, HIGH);
                digitalWrite(pinO_led_L[2], LOW);
                digitalWrite(pinO_led_R[2], LOW);
                digitalWrite(pinO_led_L[3], HIGH);
                digitalWrite(pinO_led_R[3], HIGH);
                delay(50);
                digitalWrite(pinO_led_C_Red, LOW);
                digitalWrite(pinO_led_C_Blu, LOW);
                digitalWrite(pinO_led_C_Gre, LOW);
                digitalWrite(pinO_led_L[3], LOW);
                digitalWrite(pinO_led_R[3], LOW);
                delay(50);
            }
        }
    };
}; // END: pattern() : Pattern3

//==========Pattern Randomizer==========

// Randomly play a pattern
void patternRandom()
{

    // Function initialization
    int r = random(3);
    patternDelay(pinI_pot_Delay, pinI_pot_Delay_Val, Delay_Val);

    // Pattern class object declarations
    Pattern1 pat1;
    Pattern2 pat2;
    Pattern3 pat3;
    Pattern *pat[] = {&pat1, &pat2, &pat3};

    // Run random pattern
    for (int i = 0; i < 10; i++)
    {
        pat[r]->pattern(Delay_Val_Avg);
    }
} //END: patternRandom()