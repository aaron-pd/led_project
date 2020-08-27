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

    // Pattern object declarations
    Pattern1 p1;
    Pattern2 p2;
    Pattern3 p3;
    Pattern4 p4;

    // Random number variables/values
    int rnd_Pattern;

    // Delay variables/values
    // -Random number selection
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = (random(4, 6) * 1000);
    // -Pattern run (switch/case)
    // --Bug avoidance (patternDelay() issue)
    unsigned long ms2_Current = millis();
    unsigned long ms2_Interval = 100;

    // Delay 1
    if (ms1_Current - ms1_Previous_PatternRnd >= ms1_Interval)
    {
        ms1_Previous_PatternRnd = ms1_Current;

        // Randomized pattern selection
        rnd_Pattern = random(sizeof(randomizer_Key));
    }

    // Delay 2
    if (ms2_Current - ms2_Previous_PatternRndRun >= ms2_Interval)
    {
        ms2_Previous_PatternRndRun = ms2_Current;

        // Switch/Case to run random pattern
        switch (rnd_Pattern)
        {

        // -Pattern 1
        case 0:
        {
            // One time reset and transition pattern
            while (randomizer_Key[0] == false)
            {
                reset();
                randomizer_Key[0] = true;
                transitionRandom();
            }
            // Run pattern
            p1.pattern(Delay_MapVal);
        }
        break; // END: case

        // -Pattern 2
        case 1:
        {
            // One time reset and transition pattern
            while (randomizer_Key[1] == false)
            {
                reset();
                randomizer_Key[1] = true;
                transitionRandom();
            }
            // Run pattern
            p2.pattern(Delay_MapVal);
        }
        break; // END: case

        // -Pattern 3
        case 2:
        {
            // One time reset and transition pattern
            while (randomizer_Key[2] == false)
            {
                reset();
                randomizer_Key[2] = true;
                transitionRandom();
            }
            // Run pattern
            p3.pattern(Delay_MapVal);
        }
        break; // END: case

        // -Pattern 4
        case 3:
        {
            // One time reset and transition pattern
            while (randomizer_Key[3] == false)
            {
                reset();
                randomizer_Key[3] = true;
                transitionRandom();
            }
            // Run pattern
            p4.pattern(Delay_MapVal);
        }
        break; // END: case

        // -Default case
        // --Bug avoidance
        default:
        {
            // One time reset and LED values set to 'LOW'
            reset();
        }
        break; // END: default case
        }
    }
} //END: patternRandom()