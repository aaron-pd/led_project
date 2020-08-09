//-------------------- Transition Randomizer --------------------

// Randomly play a transition pattern
void transitionRandom()
{

    // Transition object declarations
    Transition1 t1;
    Transition2 t2;
    Transition3 t3;
    Transition *transition[] = {&t1, &t2, &t3};

    // Run random transition
    transition[random(ARRAYSIZE(transition))]->transition();
} // END: transitionRandom()

//-------------------- Pattern Randomizer --------------------

// Randomly play a pattern
void patternRandom()
{

    // Random number variables/values
    int rnd_Pattern;

    // Delay variables/values
    unsigned long ms_Current = millis();
    unsigned long ms_Interval = (random(4, 6) * 1000);

    // Delay
    if (ms_Current - ms_Previous_PatternRnd >= ms_Interval)
    {
        ms_Previous_PatternRnd = ms_Current;

        // Randomized pattern selection
        rnd_Pattern = random(sizeof(randomizer_Key));
    }

    // Pattern object declarations
    Pattern1 p1;
    Pattern2 p2;
    Pattern3 p3;

    // Switch/Case to run random pattern
    switch (rnd_Pattern)
    {

    // -Case 0
    // --One-time LED reset, play transition pattern, play pattern 1
    case 0:
    {
        while (randomizer_Key[0] == true)
        {
            reset();
            randomizer_Key[0] = false;
            transitionRandom();
        }
        patternDelay(pinI_pot_Delay, pinI_pot_Delay_Val, Delay_Val);
        p1.pattern(Delay_Val_MapAvg);
    }
    break; // END: case

    // -Case 1
    // --One-time LED reset, play transition pattern, play pattern 2
    case 1:
    {
        while (randomizer_Key[1] == true)
        {
            reset();
            randomizer_Key[1] = false;
            transitionRandom();
        }
        patternDelay(pinI_pot_Delay, pinI_pot_Delay_Val, Delay_Val);
        p2.pattern(Delay_Val_MapAvg);
    }
    break; // END: case

    // -Case 2
    // --One-time LED reset, play transition pattern, play pattern 3
    case 2:
    {
        while (randomizer_Key[2] == true)
        {
            reset();
            randomizer_Key[2] = false;
            transitionRandom();
        }
        patternDelay(pinI_pot_Delay, pinI_pot_Delay_Val, Delay_Val);
        p3.pattern(Delay_Val_MapAvg);
    }
    break; // END: case

    // -Default case
    // --Bug avoidance
    default:
    {
        reset();
    }
    break; // END: default case
    }
} //END: patternRandom()