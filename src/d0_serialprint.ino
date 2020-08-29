//-------------------- Diagnostic Functions --------------------

// Input values for serial monitor print display
void serialPrint()
{

    // Delay variables/values
    unsigned long ms1_Current = millis();
    unsigned long ms1_Interval = 500;

    // Delay 1
    if (ms1_Current - ms1_Previous_Print >= ms1_Interval)
    {
        ms1_Previous_Print = ms1_Current;

        // Delay Potentiometer
        Serial.print("Delay Potentiometer:");
        Serial.print("\t");
        Serial.print(pinI_pot_Delay_Val);
        Serial.println();
        Serial.print("Delay Rate:");
        Serial.print("\t");
        Serial.print("\t");
        Serial.print(Delay_MapVal);
        Serial.println();
        // Dimmer Potentiometer
        Serial.print("Dimmer Potentiometer:");
        Serial.print("\t");
        Serial.print(pinI_pot_Dimmer_Val);
        Serial.println();
        Serial.print("Dimmer Value:");
        Serial.print("\t");
        Serial.print("\t");
        Serial.print(Dimmer_MapVal);
        Serial.println();
        // Select Potentiometer
        Serial.print("Select Potentiometer:");
        Serial.print("\t");
        Serial.print(pinI_pot_Select_Val);
        Serial.println();
        Serial.print("Select Value:");
        Serial.print("\t");
        Serial.print("\t");
        Serial.print(Select_MapVal);
        Serial.println();
        // Print separation line
        Serial.println();
        // Switch A/B
        Serial.print("Switch A:");
        Serial.print("\t");
        Serial.print(pinI_switch_PosA_Val);
        Serial.print("\t");
        Serial.print("Switch B:");
        Serial.print("\t");
        Serial.print(pinI_switch_PosB_Val);
        Serial.println();
        // Print separation line
        Serial.println();
    }
} // END: serialPrint()