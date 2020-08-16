//-------------------- Input Functions --------------------

// LED dimming control determined by potentiometer value
void dimmer()
{

    // Delay variables/values
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = 50;

    // Delay 1
    if (ms1_Current - ms1_Previous_Dimmer >= ms1_Interval)
    {
        ms1_Previous_Dimmer = ms1_Current;

        // EMA filtering
        // -Set analog read input values
        pinI_pot_Dimmer_Val = analogRead(pinI_pot_Dimmer);
        // -Calculations
        sample_MovAvg_Dimmer = (sample_Rate_Dimmer * pinI_pot_Dimmer_Val) + ((1 - sample_Rate_Dimmer) * sample_MovAvg_Dimmer);

        // Dimmer value mapped to dimmer potentiometer value with filtering calculations
        Dimmer_MapVal = map(sample_MovAvg_Dimmer, 8, 1015, 0, 255);

        // Dimness of LEDs sent to MOSFET output pin
        analogWrite(pinO_Dimmer, Dimmer_MapVal);
    }
} // END: dimmer()
