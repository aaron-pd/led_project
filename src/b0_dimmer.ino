//-------------------- Functions --------------------

// LED dimming control determined by potentiometer value
void ledDimmer()
{

  // Delay variables/values
  unsigned long currentMillis = millis();
  unsigned long intervalMillis = 50;

  // Delay
  if (currentMillis - previousMillis_Dimmer >= intervalMillis)
  {
    previousMillis_Dimmer = currentMillis;

    // EMA smoothing
    // -Set analog read input values
    potPinDimmer_Val = analogRead(potPinDimmer);
    // -calculations
    sampleAverage_Dimmer =
        (sampleRate_Dimmer * potPinDimmer_Val) + ((1 - sampleRate_Dimmer) * sampleAverage_Dimmer);

    // Dimmer value set by dimmer potentiometer with Smoothing calculations
    dimmer_Val = sampleAverage_Dimmer;
    dimmer_Val = map(potPinDimmer_Val, 8, 1015, 0, 255);

    // Dimness of lEDs sent to MOSFET output pin
    analogWrite(dimmerPin, dimmer_Val);
  }
}
