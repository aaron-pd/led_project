//-------------------- Functions --------------------

// Transition LED pattern
// -Ran after patternReset() function and before new selected pattern function
void patternTransition0() {

  digitalWrite(ledPinCRed, HIGH);
  digitalWrite(ledPinCBlue, LOW);
  digitalWrite(ledPinCGreen, LOW);
  digitalWrite(ledPinL[0], HIGH);
  digitalWrite(ledPinR[0], HIGH);
  delay(100);
  digitalWrite(ledPinCRed, HIGH);
  digitalWrite(ledPinCBlue, LOW);
  digitalWrite(ledPinCGreen, HIGH);
  digitalWrite(ledPinL[0], LOW);
  digitalWrite(ledPinR[0], LOW);
  digitalWrite(ledPinL[1], HIGH);
  digitalWrite(ledPinR[1], HIGH);
  delay(100);
  digitalWrite(ledPinCRed, LOW);
  digitalWrite(ledPinCBlue, HIGH);
  digitalWrite(ledPinCGreen, LOW);
  digitalWrite(ledPinL[1], LOW);
  digitalWrite(ledPinR[1], LOW);
  digitalWrite(ledPinL[2], HIGH);
  digitalWrite(ledPinR[2], HIGH);
  delay(100);
  digitalWrite(ledPinCRed, LOW);
  digitalWrite(ledPinCBlue, LOW);
  digitalWrite(ledPinCGreen, HIGH);
  digitalWrite(ledPinL[2], LOW);
  digitalWrite(ledPinR[2], LOW);
  digitalWrite(ledPinL[3], HIGH);
  digitalWrite(ledPinR[3], HIGH);
  delay(100);
  digitalWrite(ledPinCRed, LOW);
  digitalWrite(ledPinCBlue, LOW);
  digitalWrite(ledPinCGreen, LOW);
  digitalWrite(ledPinL[3], LOW);
  digitalWrite(ledPinR[3], LOW);
  delay(100);
}
