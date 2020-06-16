//-------------------- Functions --------------------

// LED pattern selection determined by potentiometer value
void ledSelect()
{

  // Delay variables/values
  unsigned long currentMillis = millis();
  unsigned long intervalMillis = 25;

  // EMA variables/values
  float sampleRate = 0.6;
  int sampleAverage = analogRead(potPinSelect);

  // Delay
  if (currentMillis - previousMillis_Select >= intervalMillis)
  {
    previousMillis_Select = currentMillis;

    // EMA smoothing
    // -Set analog/digital read input values
    potPinSelect_Val = analogRead(potPinSelect);
    // -calculations
    sampleAverage =
        (sampleRate * potPinSelect_Val) + ((1 - sampleRate) * sampleAverage);

    // Pattern select value set by selection potentiometer with Smoothing
    // calculations
    select_Val = sampleAverage;
    select_Val = map(potPinSelect_Val, 8, 1015, 0, 999);

    // Switch/Case used to select pattern from select_Val variable
    switch (select_Val)
    {

    // -Off
    // --One-time LED reset, set all LEDs to always 'LOW'
    case 0 ... 249:
      reset();
      ledPatterns.off();
      break;

    // -Pattern 0
    // --One-time LED reset, play transition pattern, play pattern 0
    case 250 ... 499:
      if (patternReset[0] == true)
      {
        reset();
        patternReset[0] = false;
        ledPatterns.transition0();
      }
      ledPatterns.pattern0(potPinDelay, potPinDelay_Val, delayRate_Val);
      break;

    // -Pattern 1
    // --One-time LED reset, play transition pattern, play pattern 1
    case 500 ... 749:
      if (patternReset[1] == true)
      {
        reset();
        patternReset[1] = false;
        ledPatterns.transition0();
      }
      ledPatterns.pattern1(potPinDelay, potPinDelay_Val, delayRate_Val);
      break;

    // -Pattern 2
    // --One-time LED reset, play transition pattern, play pattern 2
    case 750 ... 850:
      if (patternReset[2] == true)
      {
        reset();
        patternReset[2] = false;
        ledPatterns.transition0();
      }
      ledPatterns.pattern2(potPinDelay, potPinDelay_Val, delayRate_Val);
      break;

    // -Default State
    // --One-time LED reset, set all LEDs to always 'HIGH'
    default:
      reset();
      ledPatterns.on();
      break;
    }
  }
}
