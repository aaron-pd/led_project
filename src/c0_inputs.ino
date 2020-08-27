//-------------------- Input Functions --------------------

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
        Dimmer_MapVal = map(sample_MovAvg_Dimmer, 8, 1015, 0, 255);

        // Dimness of LEDs sent to MOSFET output pin
        analogWrite(pinO_Dimmer, Dimmer_MapVal);
    }
} // END: dimmer()

//==========Switch_AB==========

// Switch between random pattern/manual pattern selection
void switch_AB()
{

    // Set digital read switch input values
    pinI_switch_PosA_Val = digitalRead(pinI_switch_PosA);
    pinI_switch_PosB_Val = digitalRead(pinI_switch_PosB);

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

//==========Select==========

// LED pattern selection determined by potentiometer position/value
void select()
{

    // Pattern object declarations
    Pattern1 p1;
    Pattern2 p2;
    Pattern3 p3;
    Pattern4 p4;

    // Delay variables/values
    // -Potentiometer input EMA filtering
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = 100;
    // -Pattern run (switch/case)
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
        Select_MapVal = map(sample_MovAvg_Select, 8, 1015, 0, 999);
    }

    // Delay 2
    if (ms2_Current - ms2_Previous_SelectRun >= ms2_Interval)
    {
        ms2_Previous_SelectRun = ms2_Current;

        // Switch/Case to run selected pattern
        switch (Select_MapVal)
        {

        // -Off
        case 0 ... 100:
        {
            // One time reset and LED values set to 'LOW'
            reset();
        }
        break; // END: case

        // -Pattern 1
        case 101 ... 200:
        {
            // One time reset
            while (reset_Key[0] == false)
            {
                reset();
                reset_Key[0] = true;
            }
            // Run pattern
            p1.pattern(Delay_MapVal);
        }
        break; // END: case

        // -Pattern 2
        case 201 ... 300:
        {
            // One time reset
            while (reset_Key[1] == false)
            {
                reset();
                reset_Key[1] = true;
            }
            // Run pattern
            p2.pattern(Delay_MapVal);
        }
        break; // END: case

        // -Pattern 3
        case 301 ... 400:
        {
            // One time reset
            while (reset_Key[2] == false)
            {
                reset();
                reset_Key[2] = true;
            }
            // Run pattern
            p3.pattern(Delay_MapVal);
        }
        break; // END: case

        // -Pattern 4
        case 401 ... 500:
        {
            // One time reset
            while (reset_Key[3] == false)
            {
                reset();
                reset_Key[3] = true;
            }
            // Run pattern
            p4.pattern(Delay_MapVal);
        }
        break; // END: case

        // -Default case
        default:
        {
             // One time reset and LED values set to 'HIGH'
            reset();
            on();
        }
        break; // END: default case
        }
    }
} // END: select()
