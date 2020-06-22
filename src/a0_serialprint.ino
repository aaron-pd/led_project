//-------------------- Functions --------------------

// Input values for serial monitor print display
void serialPrint()
{

  // Delay variables/values
  unsigned long currentMillis = millis();
  unsigned long intervalMillis = 500;

  // Delay
  if (currentMillis - previousMillis_Print >= intervalMillis)
  {
    previousMillis_Print = currentMillis;

    // -Delay Potentiometer
    Serial.print("Delay Potentiometer:");
    Serial.print("\t");
    Serial.print(potPinDelay_Val);
    Serial.println();
    Serial.print("Delay Rate:");
    Serial.print("\t");
    Serial.print(delayRate_Val);
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
} // END: function