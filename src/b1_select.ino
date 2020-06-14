//-------------------- Functions --------------------

// LED pattern selector determined by potentiometer value
void ledSelect() {

  // Delay variables/values
  unsigned long currentMillis = millis();
  unsigned long previousMillis = 0;
  unsigned long intervalMillis = 25;
  // EMA variables/values
  float sampleRate = 0.2;
  int sampleAverage = analogRead(potPinSelect);

  // Delay
  if (currentMillis - previousMillis >= intervalMillis) {
    previousMillis = currentMillis;

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
    switch (select_Val) {

    // -Off: set LEDs to always 'LOW'
    case 0 ... 249:
      reset();
      ledOff();
      break;

    // -Pattern 0: Initial LED reset, play transition pattern, play pattern 0
    case 250 ... 499:
      if (patternReset[0] == true) {
        reset();
        patternReset[0] = false;
        patternTransition0();
      }
      pattern0();
      break;

    // -Pattern 1: Initial LED reset, play transition pattern, play pattern 1
    case 500 ... 749:
      if (patternReset[1] == true) {
        reset();
        patternReset[1] = false;
        patternTransition0();
      }
      pattern1();
      break;

    // -Pattern 2: Initial LED reset, play transition pattern, play pattern 2
    case 750 ... 900:
      if (patternReset[2] == true) {
        reset();
        patternReset[2] = false;
        patternTransition0();
      }
      pattern2();
      break;

    // -Default State: set LEDs to always 'HIGH'
    default:
      reset();
      ledOn();
      break;
    }
  }
}
