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
    Pattern *pattern[] = {&p1, &p2, &p3, &p4};

    // Delay variables/values
    // -Random number selection
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = (random(4, 6) * 1000);

    // Delay 1
    if (ms1_Current - ms1_Previous_PatternRnd >= ms1_Interval)
    {
        ms1_Previous_PatternRnd = ms1_Current;

        // Randomized pattern selection
        rnd_Pattern = random(ARRAYSIZE(pattern));
    }

    // One time reset and transition pattern
    while (reset_Key[rnd_Pattern] == false)
    {
        reset();
        reset_Key[rnd_Pattern] = true;
        transitionRandom();
    }

    // Run pattern
    pattern[rnd_Pattern]->pattern(Delay_MapVal);
} //END: patternRandom()
