//-------------------- Input Functions --------------------

// LED dimming control determined by potentiometer value
void dimmer()
{

  // Delay variables/values
  unsigned long ms_Current = millis();
  unsigned long ms_Interval = 50;

  // Delay
  if (ms_Current - ms_Previous_Dimmer >= ms_Interval)
  {
    ms_Previous_Dimmer = ms_Current;

    // EMA filtering
    // -Set analog read input values
    pinI_pot_Dimmer_Val = analogRead(pinI_pot_Dimmer);
    // -Calculations
    sample_Average_Dimmer = (sample_Rate_Dimmer * pinI_pot_Dimmer_Val) + ((1 - sample_Rate_Dimmer) * sample_Average_Dimmer);
    // -Saved values required to remember previous loop values
    Dimmer_MapVal = sample_Average_Dimmer;

    // Dimmer value mapped to dimmer potentiometer value with filtering calculations
    Dimmer_MapVal = map(pinI_pot_Dimmer_Val, 8, 1015, 0, 255);

    // Dimness of lEDs sent to MOSFET output pin
    analogWrite(pinO_Dimmer, Dimmer_MapVal);
  }
} // END: dimmer()
