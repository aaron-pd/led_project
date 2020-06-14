//-------------------- Functions --------------------

// LEDs are always on
void ledOn() {

  ledPinCRed_Val = HIGH;
  ledPinCBlue_Val = HIGH;
  ledPinCGreen_Val = HIGH;
  digitalWrite(ledPinCRed, ledPinCRed_Val);
  digitalWrite(ledPinCBlue, ledPinCBlue_Val);
  digitalWrite(ledPinCGreen, ledPinCGreen_Val);
  for (int i = 0; i < ledCount; i++) {
    ledPinL_Val[i] = HIGH;
    ledPinR_Val[i] = HIGH;
    digitalWrite(ledPinL[i], ledPinL_Val[i]);
    digitalWrite(ledPinR[i], ledPinR_Val[i]);
  }
}

// LEDs are always off
void ledOff() {

  ledPinCRed_Val = LOW;
  ledPinCBlue_Val = LOW;
  ledPinCGreen_Val = LOW;
  digitalWrite(ledPinCRed, ledPinCRed_Val);
  digitalWrite(ledPinCBlue, ledPinCBlue_Val);
  digitalWrite(ledPinCGreen, ledPinCGreen_Val);
  for (int i = 0; i < ledCount; i++) {
    ledPinL_Val[i] = LOW;
    ledPinR_Val[i] = LOW;
    digitalWrite(ledPinL[i], ledPinL_Val[i]);
    digitalWrite(ledPinR[i], ledPinR_Val[i]);
  }
}
