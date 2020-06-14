//-------------------- Functions --------------------

// Sets LED pattern, delay based on blink rate potentiometer value
// -Pattern will flash center LED, then fade through the following LEDs outwards
void pattern1() {

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
      digitalWrite(ledPinCRed, ledPinCRed_Val);
      digitalWrite(ledPinCBlue, ledPinCBlue_Val);
      digitalWrite(ledPinCGreen, ledPinCGreen_Val);
      for (int i = 0; i < ledCount; i++) {
        digitalWrite(ledPinL[i], LOW);
        digitalWrite(ledPinR[i], LOW);
      }
    } else {
      ledPinCRed_Val = LOW;
      ledPinCBlue_Val = LOW;
      ledPinCGreen_Val = LOW;
      digitalWrite(ledPinCRed, ledPinCRed_Val);
      digitalWrite(ledPinCBlue, ledPinCBlue_Val);
      digitalWrite(ledPinCGreen, ledPinCGreen_Val);
      for (int i = 0; i < ledCount; i++) {
        digitalWrite(ledPinL[i], HIGH);
        digitalWrite(ledPinR[i], HIGH);
        delay(50);
        digitalWrite(ledPinL[i], LOW);
        digitalWrite(ledPinR[i], LOW);
      }
    }
  }
}
