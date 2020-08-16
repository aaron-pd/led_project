//-------------------- Miscellaneous Functions --------------------

// -Set all reset_Key[#] and randomizer_Key[#] array values to 'true' and set all LEDs to 'LOW'
// -Usage: Check if specific reset_Key[#] or randomizer_Key[#] array is 'true', run reset() function and set
//  specific reset_Key[#] or randomizer_Key[#] array to 'false' to prevent reset() function from looping continuously
// -Used in select() and patternRandom() functions

void reset()
{

    for (unsigned int i = 0; i < sizeof(reset_Key); i++)
    {
        reset_Key[i] = true;
    }
    for (unsigned int i = 0; i < sizeof(randomizer_Key); i++)
    {
        randomizer_Key[i] = true;
    }
    off();
} // END: reset()

// LEDs are always on, values set to 'HIGH'
void on()
{

    pinO_led_C_Red_Val = HIGH;
    pinO_led_C_Blu_Val = HIGH;
    pinO_led_C_Grn_Val = HIGH;
    digitalWrite(pinO_led_C_Red, pinO_led_C_Red_Val);
    digitalWrite(pinO_led_C_Blu, pinO_led_C_Blu_Val);
    digitalWrite(pinO_led_C_Grn, pinO_led_C_Grn_Val);
    for (int i = 0; i < led_LR_Count; i++)
    {
        pinO_led_L_Val[i] = HIGH;
        pinO_led_R_Val[i] = HIGH;
        digitalWrite(pinO_led_L[i], pinO_led_L_Val[i]);
        digitalWrite(pinO_led_R[i], pinO_led_R_Val[i]);
    }
} // END: on()

// LEDs are always off, values set to 'LOW'
void off()
{

    pinO_led_C_Red_Val = LOW;
    pinO_led_C_Blu_Val = LOW;
    pinO_led_C_Grn_Val = LOW;
    digitalWrite(pinO_led_C_Red, pinO_led_C_Red_Val);
    digitalWrite(pinO_led_C_Blu, pinO_led_C_Blu_Val);
    digitalWrite(pinO_led_C_Grn, pinO_led_C_Grn_Val);
    for (int i = 0; i < led_LR_Count; i++)
    {
        pinO_led_L_Val[i] = LOW;
        pinO_led_R_Val[i] = LOW;
        digitalWrite(pinO_led_L[i], pinO_led_L_Val[i]);
        digitalWrite(pinO_led_R[i], pinO_led_R_Val[i]);
    }
} // END: off()

//-------------------- Pattern Delay Input Filtering --------------------

// Pattern delay calculations with EMA filtering
// -Final calculated 'Delay_MapVal' used by pattern(#) functions
void patternDelay()
{

    // Delay variables/values
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = 115;

    // Delay 1
    if (ms1_Current - ms1_Previous_Delay >= ms1_Interval)
    {
        ms1_Previous_Delay = ms1_Current;

        // EMA filtering
        // -Set analog read input values
        pinI_pot_Delay_Val = analogRead(pinI_pot_Delay);
        // -Calculations
        sample_MovAvg_Delay = (sample_Rate_Delay * pinI_pot_Delay_Val) + ((1 - sample_Rate_Delay) * sample_MovAvg_Delay);

        // Delay value mapped to delay potentiometer value with filtering calculations
        Delay_MapVal = map(sample_MovAvg_Delay, 8, 1015, 0, 255);
        
        // Pattern/Transition delay value update
        pattern_Delay = (sample_MovAvg_Delay / 4);
        transition_Delay = (sample_MovAvg_Delay / 2);
    }
} // END: patternDelay()