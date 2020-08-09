//-------------------- Diagnostic Functions --------------------

// Input values for serial monitor print display
void serialPrint()
{

    // Delay variables/values
    unsigned long ms_Current = millis();
    unsigned long ms_Interval = 500;

    // Delay
    if (ms_Current - ms_Previous_Print >= ms_Interval)
    {
        ms_Previous_Print = ms_Current;

        // -Delay Potentiometer
        Serial.print("Delay Potentiometer:");
        Serial.print("\t");
        Serial.print(pinI_pot_Delay_Val);
        Serial.println();
        Serial.print("Delay Rate:");
        Serial.print("\t");
        Serial.print("\t");
        Serial.print(Delay_Val_MapAvg);
        Serial.println();
        // -Dimmer Potentiometer
        Serial.print("Dimmer Potentiometer:");
        Serial.print("\t");
        Serial.print(pinI_pot_Dimmer_Val);
        Serial.println();
        Serial.print("Dimmer Value:");
        Serial.print("\t");
        Serial.print("\t");
        Serial.print(Dimmer_Val_MapVal);
        Serial.println();
        // -Select Potentiometer
        Serial.print("Select Potentiometer:");
        Serial.print("\t");
        Serial.print(pinI_pot_Select_Val);
        Serial.println();
        Serial.print("Select Value:");
        Serial.print("\t");
        Serial.print("\t");
        Serial.print(Select_Val_MapVal);
        Serial.println();
        Serial.println();
        // -3-Way Switch A/B
        Serial.print("Switch A:");
        Serial.print("\t");
        Serial.print(pinI_switch_PosA_Val);
        Serial.print("\t");
        Serial.print("Switch B:");
        Serial.print("\t");
        Serial.print(pinI_switch_PosB_Val);
        Serial.println();
        Serial.println();
    }
} // END: serialPrint()