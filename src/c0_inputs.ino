//-------------------- Input Functions --------------------

//==========Switch_AB==========

// Switch between random pattern/manual pattern selection
void switch_AB()
{

    // Read switch input values
    pinI_switch_PosA_Val = digitalRead(pinI_switch_PosA);
    pinI_switch_PosB_Val = digitalRead(pinI_switch_PosB);

    // Reset key variables/values
    // -'false' declaration to avoid delayed start up
    // -Static variables required to remember previous loop values
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

//==========Dimmer==========

// LED dimming control determined by potentiometer value
void dimmer()
{

    // Delay variables/values
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = 100;

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
        Dimmer_MapVal = map(sample_MovAvg_Dimmer, 8, 1015, 50, 250);

        // Dimness of LEDs sent to MOSFET output pin
        analogWrite(pinO_Dimmer, Dimmer_MapVal);
    }
} // END: dimmer()

//==========Pattern Delay Input Filtering==========

// Pattern delay potentiometer input value calculations with EMA filtering
// -Final calculated variable 'Delay_MapVal' used by pattern() functions
void patternDelay()
{

    // Delay variables/values
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = 100;

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
        Delay_MapVal = map(sample_MovAvg_Delay, 8, 1015, 50, 250);

        // Global pattern/transition delay values update
        pattern_Delay = (sample_MovAvg_Delay / 4);
        transition_Delay = (sample_MovAvg_Delay / 2);
    }
} // END: patternDelay()

//==========Select==========

// LED pattern selection determined by potentiometer position/value
void select()
{

    // Pattern object declarations
    Pattern1 p1;
    Pattern2 p2;
    Pattern3 p3;
    Pattern4 p4;
    Pattern *pattern[] = {&p1, &p2, &p3, &p4};

    // Delay variables/values
    // -Potentiometer input EMA filtering
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = 100;
    // -Pattern run
    // -Bug avoidance
    unsigned long ms2_Current = millis();
    unsigned long ms2_Interval = 100;

    // Delay 1
    if (ms1_Current - ms1_Previous_Select >= ms1_Interval)
    {
        ms1_Previous_Select = ms1_Current;

        // EMA filtering
        // -Set analog read input values
        pinI_pot_Select_Val = analogRead(pinI_pot_Select);
        // -Calculations
        sample_MovAvg_Select = (sample_Rate_Select * pinI_pot_Select_Val) + ((1 - sample_Rate_Select) * sample_MovAvg_Select);

        // Pattern select value mapped to select potentiometer value with filtering calculations
        Select_MapVal = map(sample_MovAvg_Select, 8, 1015, 0, (patternSize + 2));
    }

    // Delay 2
    if (ms2_Current - ms2_Previous_SelectRun >= ms2_Interval)
    {
        ms2_Previous_SelectRun = ms2_Current;

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
            pattern[Select_MapVal - 1]->pattern(Delay_MapVal);
        }

        // On
        else
        {
            // One time reset and LED values set to 'HIGH'
            reset();
            on();
        }
    }
} // END: select()