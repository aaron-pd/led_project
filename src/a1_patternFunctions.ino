//-------------------- Functions --------------------

// Set all of patternReset[] array to 'true' and set all LEDs to 'LOW'
// Usage: Check if specific patternReset[#] array is 'true', run patternReset()
// function, set specific patternReset[#] array to 'false' to prevent
// patternReset() function from running agian (see ledSelect() function)

void reset()
{

  for (int i = 0; i < patternResetCount; i++)
  {
    patternReset[i] = true;
  }
  off();
} // END: reset

// LEDs are always on
void on()
{

  ledPinCRed_Val = HIGH;
  ledPinCBlue_Val = HIGH;
  ledPinCGreen_Val = HIGH;
  digitalWrite(ledPinCRed, ledPinCRed_Val);
  digitalWrite(ledPinCBlue, ledPinCBlue_Val);
  digitalWrite(ledPinCGreen, ledPinCGreen_Val);
  for (int i = 0; i < ledCount; i++)
  {
    ledPinL_Val[i] = HIGH;
    ledPinR_Val[i] = HIGH;
    digitalWrite(ledPinL[i], ledPinL_Val[i]);
    digitalWrite(ledPinR[i], ledPinR_Val[i]);
  }
} // END: on

// LEDs are always off
void off()
{

  ledPinCRed_Val = LOW;
  ledPinCBlue_Val = LOW;
  ledPinCGreen_Val = LOW;
  digitalWrite(ledPinCRed, ledPinCRed_Val);
  digitalWrite(ledPinCBlue, ledPinCBlue_Val);
  digitalWrite(ledPinCGreen, ledPinCGreen_Val);
  for (int i = 0; i < ledCount; i++)
  {
    ledPinL_Val[i] = LOW;
    ledPinR_Val[i] = LOW;
    digitalWrite(ledPinL[i], ledPinL_Val[i]);
    digitalWrite(ledPinR[i], ledPinR_Val[i]);
  }
} // END: off
