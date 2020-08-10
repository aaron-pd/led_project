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
    // -Random number selection
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = (random(4, 6) * 1000);
    // -Pattern run (switch/case)
    // --Bug avoidance (patternDelay() issue)
    unsigned long ms2_Current = millis();
    unsigned long ms2_Interval = 100;

    // Delay 1
    if (ms1_Current - ms_Previous_PatternRnd >= ms1_Interval)
    {
        ms_Previous_PatternRnd = ms1_Current;

        // Randomized pattern selection
        rnd_Pattern = random(sizeof(randomizer_Key));
    }

    // Delay 2
    if (ms2_Current - ms_Previous_PatternRndRun >= ms2_Interval)
    {
        ms_Previous_PatternRndRun = ms2_Current;

        // Switch/Case to run random pattern
        switch (rnd_Pattern)
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
    }
} //END: patternRandom()