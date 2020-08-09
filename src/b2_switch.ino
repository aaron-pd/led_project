//-------------------- Input Functions --------------------

// Control to switch between random pattern/manual pattern selection with 3-way switch
void switch_AB()
{

    // Set digital read switch input values
    pinI_switch_PosA_Val = digitalRead(pinI_switch_PosA);
    pinI_switch_PosB_Val = digitalRead(pinI_switch_PosB);

    // Switch position 'A'
    // -Play selected patterns only
    if (pinI_switch_PosA_Val == HIGH)
    {
        while (switch_PosA_Key == true)
        {
            reset();
            switch_PosA_Key = false;
            switch_PosB_Key = true;
        }
        select();
    } // END: if

    // Switch position 'B'
    // -Play all patterns randomly
    else if (pinI_switch_PosB_Val == HIGH)
    {
        while (switch_PosB_Key == true)
        {
            reset();
            switch_PosA_Key = true;
            switch_PosB_Key = false;
        }
        patternRandom();
    } // END: if

    // Turn all LEDs off if switch state is undetermined
    // -Bug avoidance
    else
    {
        reset();
        switch_PosA_Key = true;
        switch_PosB_Key = true;
    } // END: else
} // END: switch_AB()
