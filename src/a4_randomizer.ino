//-------------------- Transition Randomizer --------------------

// Randomly play a transition pattern
void transitionRandom()
{

    // Transition object declarations
    Transition1 t1;
    Transition2 t2;
    Transition3 t3;
    Transition *transition[] ={ &t1, &t2, &t3 };

    // Run random transition
    transition[random(ARRAYSIZE(transition))]->transition();
} // END: transitionRandom()

//-------------------- Pattern Randomizer --------------------

// Randomly play a pattern
void patternRandom()
{

    // Pattern object declarations
    Pattern1 p1;
    Pattern2 p2;
    Pattern3 p3;

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

    // Switch/Case to run random pattern
    switch (0)
    {

        // -Pattern 1
        // --One-time LED reset, play transition pattern, play pattern 1
    case 0:
    {
        while (randomizer_Key[0] == true)
        {
            reset();
            randomizer_Key[0] = false;
            transitionRandom();
        }
        patternDelay();
        p1.pattern(Delay_Val_MapAvg);
    }
    break; // END: case

    // -Pattern 2
    // --One-time LED reset, play transition pattern, play pattern 2
    case 1:
    {
        while (randomizer_Key[1] == true)
        {
            reset();
            randomizer_Key[1] = false;
            transitionRandom();
        }
        patternDelay();
        p2.pattern(Delay_Val_MapAvg);
    }
    break; // END: case

    // -Pattern 3
    // --One-time LED reset, play transition pattern, play pattern 3
    case 2:
    {
        while (randomizer_Key[2] == true)
        {
            reset();
            randomizer_Key[2] = false;
            transitionRandom();
        }
        patternDelay();
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