//-------------------- Functions --------------------

// LED pattern selection determined by potentiometer value
void select()
{

  // Pattern function object declarations
  Pattern1 pat1;
  Pattern2 pat2;
  Pattern3 pat3;

  // Delay variables/values
  unsigned long currentMillis = millis();
  unsigned long intervalMillis = 25;

  // Delay
  if (currentMillis - previousMillis_Select >= intervalMillis)
  {
    previousMillis_Select = currentMillis;

    // EMA smoothing
    // -Set analog read input values
    potPinSelect_Val = analogRead(potPinSelect);
    // -calculations
    sampleAverage_Select =
        (sampleRate_Select * potPinSelect_Val) + ((1 - sampleRate_Select) * sampleAverage_Select);

    // Pattern select value set by selection potentiometer with Smoothing
    // calculations
    select_Val = sampleAverage_Select;
    select_Val = map(potPinSelect_Val, 8, 1015, 0, 999);

    // Switch/Case used to select pattern from select_Val variable
    switch (select_Val)
    {

    // -Off
    // --One-time LED reset, set all LEDs to always 'LOW'
    case 0 ... 249:
      reset();
      off();
      break;

    // -Pattern 1
    // --One-time LED reset, play transition pattern, play pattern 1
    case 250 ... 499:
      if (patternReset[0] == true)
      {
        reset();
        patternReset[0] = false;
        transitionRandom();
      }
      patternDelay(potPinDelay, potPinDelay_Val, delayRate_Val);
      pat1.pattern(delay_Val_AVG);
      break;

    // -Pattern 2
    // --One-time LED reset, play transition pattern, play pattern 2
    case 500 ... 749:
      if (patternReset[1] == true)
      {
        reset();
        patternReset[1] = false;
        transitionRandom();
      }
      patternDelay(potPinDelay, potPinDelay_Val, delayRate_Val);
      pat2.pattern(delay_Val_AVG);
      break;

    // -Pattern 3
    // --One-time LED reset, play transition pattern, play pattern 3
    case 750 ... 850:
      if (patternReset[2] == true)
      {
        reset();
        patternReset[2] = false;
        transitionRandom();
      }
      patternDelay(potPinDelay, potPinDelay_Val, delayRate_Val);
      pat3.pattern(delay_Val_AVG);
      break;

    // -Default State
    // --One-time LED reset, set all LEDs to always 'HIGH'
    default:
      reset();
      on();
      break;
    }
  }
} // END: select
