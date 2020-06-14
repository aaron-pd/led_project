//-------------------- Functions --------------------

// LED dimming control determined by potentiometer value
void ledDimmer() {

  // Delay variables/values
  unsigned long currentMillis = millis();
  unsigned long previousMillis = 0;
  unsigned long intervalMillis = 25;
  // EMA variables/values
  float sampleRate = 0.2;
  int sampleAverage = analogRead(potPinDimmer); /////REVIEW
  // Causing slow down? move to global variables & setup()?

  // Delay
  if (currentMillis - previousMillis >= intervalMillis) {
    previousMillis = currentMillis;

    // EMA smoothing
    // -Set analog/digital read input values
    potPinDimmer_Val = analogRead(potPinDimmer);
    // -calculations
    sampleAverage =
        (sampleRate * potPinDimmer_Val) + ((1 - sampleRate) * sampleAverage);

    // Dimmer value set by dimmer potentiometer with Smoothing calculations
    dimmer_Val = sampleAverage;
    dimmer_Val = map(potPinDimmer_Val, 8, 1015, 0, 255);

    // Dimness of lEDs sent to MOSFET output pin
    analogWrite(dimmerPin, dimmer_Val);
  }
}
