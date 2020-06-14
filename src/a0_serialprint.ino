//-------------------- Functions --------------------

// Input values for serial monitor print display
void serialPrint() {

  // -Blink Potentiometer
  Serial.print("Blink Potentiometer:");
  Serial.print("\t");
  Serial.print(potPinBlink_Val);
  Serial.println();
  Serial.print("Blink Rate:");
  Serial.print("\t");
  Serial.print(blinkRate_Val);
  Serial.println();
  // -Dimmer Potentiometer
  Serial.print("Dimmer Potentiometer:");
  Serial.print("\t");
  Serial.print(potPinDimmer_Val);
  Serial.println();
  Serial.print("Dimmer Value:");
  Serial.print("\t");
  Serial.print(dimmer_Val);
  Serial.println();
  // -Select Potentiometer
  Serial.print("Select Potentiometer:");
  Serial.print("\t");
  Serial.print(potPinSelect_Val);
  Serial.println();
  Serial.print("Select Value:");
  Serial.print("\t");
  Serial.print(select_Val);
  Serial.println();
  Serial.println();
  // -Switch
  Serial.print("Switch A:");
  Serial.print("\t");
  Serial.print(switchPin_PosA_Val);
  Serial.print("\t");
  Serial.print("Switch B:");
  Serial.print("\t");
  Serial.print(switchPin_PosB_Val);
  Serial.println();
  Serial.println();
}
