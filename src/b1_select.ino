//-------------------- Input Functions --------------------

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
            while (reset_Key[0] == true)
            {
                reset();
                reset_Key[0] = false;
            }
            // Run pattern
            p1.pattern(Delay_MapVal);
        }
        break; // END: case

        // -Pattern 2
        case 201 ... 300:
        {
            // One time reset
            while (reset_Key[1] == true)
            {
                reset();
                reset_Key[1] = false;
            }
            // Run pattern
            p2.pattern(Delay_MapVal);
        }
        break; // END: case

        // -Pattern 3
        case 301 ... 400:
        {
            // One time reset
            while (reset_Key[2] == true)
            {
                reset();
                reset_Key[2] = false;
            }
            // Run pattern
            p3.pattern(Delay_MapVal);
        }
        break; // END: case

        // -Pattern 4
        case 401 ... 500:
        {
            // One time reset
            while (reset_Key[3] == true)
            {
                reset();
                reset_Key[3] = false;
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
