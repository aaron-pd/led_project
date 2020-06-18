//-------------------- Functions --------------------

// Control to switch between random pattern/manual pattern selection with 3-way
// switch
void ledSwitch()
{

  // Set digital read switch input values
  switchPin_PosA_Val = digitalRead(switchPin_PosA);
  switchPin_PosB_Val = digitalRead(switchPin_PosB);

  // Switch position 'A'
  // -Play all patterns randomly
  if (switchPin_PosA_Val == HIGH)
  {
    reset();
    ledPatterns.patternDelay(potPinDelay, potPinDelay_Val, delayRate_Val);
    ledPatterns.patternRND(ledPatterns.delay_Val_AVG);
  }

  // Switch position 'B'
  // -Play selected patterns only
  if (switchPin_PosB_Val == HIGH)
  {
    ledSelect();
  }
}