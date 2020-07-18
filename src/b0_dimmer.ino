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
    // -calculations
    sample_Average_Dimmer = (sample_Rate_Dimmer * pinI_pot_Dimmer_Val) + ((1 - sample_Rate_Dimmer) * sample_Average_Dimmer);

    // Dimmer value set by dimmer potentiometer with filtering calculations
    pinO_Dimmer_Val = sample_Average_Dimmer;
    pinO_Dimmer_Val = map(pinI_pot_Dimmer_Val, 8, 1015, 0, 255);

    // Dimness of lEDs sent to MOSFET output pin
    analogWrite(pinO_Dimmer, pinO_Dimmer_Val);
  }
} // END: dimmer()
