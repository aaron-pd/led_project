//-------------------- Repeating Pattern Functions --------------------

// Pattern delay calculations with EMA smoothing
// -Function requires potentiometer input pin, input pin value and outside-of-function delay value
void patternDelay(int pot_Pin, int pot_Val, unsigned long delay_Val_EMA)
{

    // Delay variables/values
    unsigned long currentMillis = millis();
    unsigned long intervalMillis = 50;

    // Delay
    if (currentMillis - previousMillis_Delay >= intervalMillis)
    {
        previousMillis_Delay = currentMillis;

        // EMA smoothing
        // -Set analog read input values
        pot_Val = analogRead(pot_Pin);
        // -calculations
        sampleAverage_Delay =
            (sampleRate_Delay * pot_Val) + ((1 - sampleRate_Delay) * sampleAverage_Delay);
        // Delay value set by delay potentiometer with Smoothing calculations
        delay_Val_EMA = sampleAverage_Delay;
        delay_Val_EMA = map(pot_Val, 8, 1015, 0, 255);
        // Set value for global variable
        delay_Val_AVG = delay_Val_EMA;
    }
} // END: patternDelay

//==========Classes==========

// Base Class
class Pattern
{
public:
    virtual void pattern(unsigned long delay_val);
};

// Derived Class 1
// Sets LED pattern, delay based on variable delay value
// -Pattern will flash all LEDs simultaneously
// -delay_Val = user custom value or smoothed input variable 'delay_Val_AVG' from 'patternDelay()' function
class Pattern1 : public Pattern
{
public:
    void pattern(unsigned long delay_Val)
    {

        // Delay variables/values
        unsigned long currentMillis = millis();

        // Delay
        if (currentMillis - previousMillis_Pattern >= delay_Val)
        {
            previousMillis_Pattern = currentMillis;

            // LED pattern
            if (ledPinCRed_Val == LOW && ledPinCBlue_Val == LOW &&
                ledPinCGreen_Val == LOW)
            {
                ledPinCRed_Val = HIGH;
                ledPinCBlue_Val = HIGH;
                ledPinCGreen_Val = HIGH;
                for (int i = 0; i < ledCount; i++)
                {
                    if (ledPinL_Val[i] == LOW && ledPinR_Val[i] == LOW)
                    {
                        ledPinL_Val[i] = HIGH;
                        ledPinR_Val[i] = HIGH;
                    }
                }
            }
            else
            {
                ledPinCRed_Val = LOW;
                ledPinCBlue_Val = LOW;
                ledPinCGreen_Val = LOW;
                for (int i = 0; i < ledCount; i++)
                {
                    if (ledPinL_Val[i] == HIGH && ledPinR_Val[i] == HIGH)
                    {
                        ledPinL_Val[i] = LOW;
                        ledPinR_Val[i] = LOW;
                    }
                }
            }
        }

        // Display LEDs based on values from previous if/else statement
        digitalWrite(ledPinCRed, ledPinCRed_Val);
        digitalWrite(ledPinCBlue, ledPinCBlue_Val);
        digitalWrite(ledPinCGreen, ledPinCGreen_Val);
        for (int i = 0; i < ledCount; i++)
        {
            digitalWrite(ledPinL[i], ledPinL_Val[i]);
            digitalWrite(ledPinR[i], ledPinR_Val[i]);
        }
    };
}; // END: pattern1

// Derived Class 2
// Sets LED pattern, delay based on variable delay value
// -Pattern will flash center LED, then fade through the following LEDs outwards
// -delay_Val = user custom value or smoothed input variable 'delay_Val_AVG' from 'patternDelay()' function
class Pattern2 : public Pattern
{
public:
    void pattern(unsigned long delay_Val)
    {

        // Delay variables/values
        unsigned long currentMillis = millis();

        // Delay
        if (currentMillis - previousMillis_Pattern >= delay_Val)
        {
            previousMillis_Pattern = currentMillis;

            // LED pattern
            if (ledPinCRed_Val == LOW && ledPinCBlue_Val == LOW &&
                ledPinCGreen_Val == LOW)
            {
                ledPinCRed_Val = HIGH;
                ledPinCBlue_Val = HIGH;
                ledPinCGreen_Val = HIGH;
                digitalWrite(ledPinCRed, ledPinCRed_Val);
                digitalWrite(ledPinCBlue, ledPinCBlue_Val);
                digitalWrite(ledPinCGreen, ledPinCGreen_Val);
                for (int i = 0; i < ledCount; i++)
                {
                    digitalWrite(ledPinL[i], LOW);
                    digitalWrite(ledPinR[i], LOW);
                }
            }
            else
            {
                ledPinCRed_Val = LOW;
                ledPinCBlue_Val = LOW;
                ledPinCGreen_Val = LOW;
                digitalWrite(ledPinCRed, ledPinCRed_Val);
                digitalWrite(ledPinCBlue, ledPinCBlue_Val);
                digitalWrite(ledPinCGreen, ledPinCGreen_Val);
                for (int i = 0; i < ledCount; i++)
                {
                    digitalWrite(ledPinL[i], HIGH);
                    digitalWrite(ledPinR[i], HIGH);
                    delay(50);
                    digitalWrite(ledPinL[i], LOW);
                    digitalWrite(ledPinR[i], LOW);
                }
            }
        }
    };
}; // END: pattern2

// Derived Class 3
// Sets LED pattern, delay based on variable delay value
// -Pattern will flash center LED, then fade through the following LEDs outwards, center LED flashes through each colour
// -delay_Val = user custom value or smoothed input variable 'delay_Val_AVG' from 'patternDelay()' function
class Pattern3 : public Pattern
{
public:
    void pattern(unsigned long delay_Val)
    {

        // Delay variables/values
        unsigned long currentMillis = millis();

        // Delay
        if (currentMillis - previousMillis_Pattern >= delay_Val)
        {
            previousMillis_Pattern = currentMillis;

            // LED pattern
            if (ledPinCRed_Val == LOW && ledPinCBlue_Val == LOW &&
                ledPinCGreen_Val == LOW)
            {
                ledPinCRed_Val = HIGH;
                ledPinCBlue_Val = HIGH;
                ledPinCGreen_Val = HIGH;
                digitalWrite(ledPinCRed, ledPinCRed_Val);
                digitalWrite(ledPinCBlue, ledPinCBlue_Val);
                digitalWrite(ledPinCGreen, ledPinCGreen_Val);
                for (int i = 0; i < ledCount; i++)
                {
                    digitalWrite(ledPinL[i], LOW);
                    digitalWrite(ledPinR[i], LOW);
                }
            }
            else
            {
                ledPinCRed_Val = LOW;
                ledPinCBlue_Val = LOW;
                ledPinCGreen_Val = LOW;
                digitalWrite(ledPinCRed, HIGH);
                digitalWrite(ledPinCBlue, LOW);
                digitalWrite(ledPinCGreen, LOW);
                digitalWrite(ledPinL[0], HIGH);
                digitalWrite(ledPinR[0], HIGH);
                delay(50);
                digitalWrite(ledPinCRed, HIGH);
                digitalWrite(ledPinCBlue, LOW);
                digitalWrite(ledPinCGreen, HIGH);
                digitalWrite(ledPinL[0], LOW);
                digitalWrite(ledPinR[0], LOW);
                digitalWrite(ledPinL[1], HIGH);
                digitalWrite(ledPinR[1], HIGH);
                delay(50);
                digitalWrite(ledPinCRed, LOW);
                digitalWrite(ledPinCBlue, HIGH);
                digitalWrite(ledPinCGreen, LOW);
                digitalWrite(ledPinL[1], LOW);
                digitalWrite(ledPinR[1], LOW);
                digitalWrite(ledPinL[2], HIGH);
                digitalWrite(ledPinR[2], HIGH);
                delay(50);
                digitalWrite(ledPinCRed, LOW);
                digitalWrite(ledPinCBlue, LOW);
                digitalWrite(ledPinCGreen, HIGH);
                digitalWrite(ledPinL[2], LOW);
                digitalWrite(ledPinR[2], LOW);
                digitalWrite(ledPinL[3], HIGH);
                digitalWrite(ledPinR[3], HIGH);
                delay(50);
                digitalWrite(ledPinCRed, LOW);
                digitalWrite(ledPinCBlue, LOW);
                digitalWrite(ledPinCGreen, LOW);
                digitalWrite(ledPinL[3], LOW);
                digitalWrite(ledPinR[3], LOW);
                delay(50);
            }
        }
    };
}; // END: pattern3

//==========Pattern Randomizer==========

// Randomly play a pattern
void patternRandom()
{

    // Function initialization
    int r = random(3);

    patternDelay(potPinDelay, potPinDelay_Val, delayRate_Val);

    // Pattern function object delcaration
    Pattern1 pat1;
    Pattern2 pat2;
    Pattern3 pat3;
    Pattern *pat[] = {&pat1, &pat2, &pat3};

    // Run pattern
    for (int i = 0; i < 10; i++)
    {
        pat[r]->pattern(delay_Val_AVG);
        delay(1);
    }
} //END: patternRandom