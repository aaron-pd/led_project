//-------------------- Functions --------------------

// Sets LED pattern, delay based on blink rate potentiometer value
// -Pattern will flash all LEDs simultaneously
void pattern0() {

  // Blink Rate
  // -Set analog/digital read input values /////REVIEW
  potPinBlink_Val = analogRead(potPinBlink); /////REVIEW
  // -Blink rate value mapped to blink potentiometer /////REVIEW
  blinkRate_Val = map(potPinBlink_Val, 8, 1015, 0, 999); /////REVIEW

  // Delay variables/values
  unsigned long currentMillis = millis();

  // Delay
  if (currentMillis - previousMillis_Pattern >= blinkRate_Val) {
    previousMillis_Pattern = currentMillis;

    // LED blink pattern
    if (ledPinCRed_Val == LOW && ledPinCBlue_Val == LOW &&
        ledPinCGreen_Val == LOW) {
      ledPinCRed_Val = HIGH;
      ledPinCBlue_Val = HIGH;
      ledPinCGreen_Val = HIGH;
      for (int i = 0; i < ledCount; i++) {
        if (ledPinL_Val[i] == LOW && ledPinR_Val[i] == LOW) {
          ledPinL_Val[i] = HIGH;
          ledPinR_Val[i] = HIGH;
        }
      }
    } else {
      ledPinCRed_Val = LOW;
      ledPinCBlue_Val = LOW;
      ledPinCGreen_Val = LOW;
      for (int i = 0; i < ledCount; i++) {
        if (ledPinL_Val[i] == HIGH && ledPinR_Val[i] == HIGH) {
          ledPinL_Val[i] = LOW;
          ledPinR_Val[i] = LOW;
        }
      }
    }
  }

  // Display LEDs based on values from previous if/else statement
  digitalWrite(ledPinCRed, ledPinCRed_Val);
  digitalWrite(ledPinCBlue, ledPinCBlue_Val);
  digitalWrite(ledPinCGreen, ledPinCGreen_Val);
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPinL[i], ledPinL_Val[i]);
    digitalWrite(ledPinR[i], ledPinR_Val[i]);
  }
}
