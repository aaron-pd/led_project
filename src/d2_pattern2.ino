//-------------------- Functions --------------------

// Sets LED pattern, delay based on blink rate potentiometer value
// -Pattern will flash center LED, then fade through the following LEDs outwards
// while the center LED matches each colour currently lit
void pattern2() {

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
      digitalWrite(ledPinCRed, HIGH);
      digitalWrite(ledPinCBlue, LOW);
      digitalWrite(ledPinCGreen, LOW);
      digitalWrite(ledPinL[0], HIGH);
      digitalWrite(ledPinR[0], HIGH);
      delay(50);
      digitalWrite(ledPinCRed, HIGH);
      digitalWrite(ledPinCBlue, LOW);
      digitalWrite(ledPinCGreen, HIGH);
      digitalWrite(ledPinL[0], LOW);
      digitalWrite(ledPinR[0], LOW);
      digitalWrite(ledPinL[1], HIGH);
      digitalWrite(ledPinR[1], HIGH);
      delay(50);
      digitalWrite(ledPinCRed, LOW);
      digitalWrite(ledPinCBlue, HIGH);
      digitalWrite(ledPinCGreen, LOW);
      digitalWrite(ledPinL[1], LOW);
      digitalWrite(ledPinR[1], LOW);
      digitalWrite(ledPinL[2], HIGH);
      digitalWrite(ledPinR[2], HIGH);
      delay(50);
      digitalWrite(ledPinCRed, LOW);
      digitalWrite(ledPinCBlue, LOW);
      digitalWrite(ledPinCGreen, HIGH);
      digitalWrite(ledPinL[2], LOW);
      digitalWrite(ledPinR[2], LOW);
      digitalWrite(ledPinL[3], HIGH);
      digitalWrite(ledPinR[3], HIGH);
      delay(50);
      digitalWrite(ledPinCRed, LOW);
      digitalWrite(ledPinCBlue, LOW);
      digitalWrite(ledPinCGreen, LOW);
      digitalWrite(ledPinL[3], LOW);
      digitalWrite(ledPinR[3], LOW);
      delay(50);
    }
  }
}
