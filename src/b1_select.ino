//-------------------- Input Functions --------------------

// LED pattern selection determined by potentiometer position/value
void select()
{

  // Pattern object declarations
  Pattern1 p1;
  Pattern2 p2;
  Pattern3 p3;

  // Delay variables/values
  unsigned long ms_Current = millis();
  unsigned long ms_Interval = 25;

  // Delay
  if (ms_Current - ms_Previous_Select >= ms_Interval)
  {
    ms_Previous_Select = ms_Current;

    // EMA filtering
    // -Set analog read input values
    pinI_pot_Select_Val = analogRead(pinI_pot_Select);
    // -Calculations
    sample_Average_Select = (sample_Rate_Select * pinI_pot_Select_Val) + ((1 - sample_Rate_Select) * sample_Average_Select);
    // -Saved values required to remember previous loop values
    Select_Val = sample_Average_Select;

    // Pattern select value mapped to select potentiometer value with filtering calculations
    Select_MapVal = map(pinI_pot_Select_Val, 8, 1015, 0, 999);

    // Switch/Case used to select pattern from Select_MapVal variable
    switch (Select_MapVal)
    {

    // -Off
    // --One-time LED reset, set all LEDs to always 'LOW'
    case 0 ... 249:
    {
      reset();
    }
    break; // END: case

    // -Pattern 1
    // --One-time LED reset, play transition pattern, play pattern 1
    case 250 ... 499:
    {
      while (reset_Key[0] == true)
      {
        reset();
        reset_Key[0] = false;
        transitionRandom();
      }
      patternDelay();
      p1.pattern(Delay_Val_MapAvg);
    }
    break; // END: case

    // -Pattern 2
    // --One-time LED reset, play transition pattern, play pattern 2
    case 500 ... 749:
    {
      while (reset_Key[1] == true)
      {
        reset();
        reset_Key[1] = false;
        transitionRandom();
      }
      patternDelay();
      p2.pattern(Delay_Val_MapAvg);
    }
    break; // END: case

    // -Pattern 3
    // --One-time LED reset, play transition pattern, play pattern 3
    case 750 ... 850:
    {
      while (reset_Key[2] == true)
      {
        reset();
        reset_Key[2] = false;
        transitionRandom();
      }
      patternDelay();
      p3.pattern(Delay_Val_MapAvg);
    }
    break; // END: case

    // -Default case
    // --One-time LED reset, set all LEDs to always 'HIGH'
    default:
    {
      reset();
      on();
    }
    break; // END: default case
    }
  }
} // END: select()
