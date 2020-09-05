//-------------------- Miscellaneous Functions --------------------

// Set reset_Key[#] and sequence_Key to 'false' and all LEDs to 'LOW'
// -reset_Key[#] used in select() and patternRandom() functions
// -sequence_Key used in all pattern(#) functions
// -Usage: run reset() function then set value to 'true' for chosen array
void reset()
{

    for (unsigned int i = 0; i < sizeof(reset_Key); i++)
    {
        reset_Key[i] = false;
    }
    sequence_Key = false;
    off();
} // END: reset()

// LEDs are always on, values set to 'HIGH'
void on()
{

    digitalWrite(pinO_led_C_Red, HIGH);
    digitalWrite(pinO_led_C_Blu, HIGH);
    digitalWrite(pinO_led_C_Grn, HIGH);
    for (int i = 0; i < led_LR_Count; i++)
    {
        digitalWrite(pinO_led_L[i], HIGH);
        digitalWrite(pinO_led_R[i], HIGH);
    }
} // END: on()

// LEDs are always off, values set to 'LOW'
void off()
{
    digitalWrite(pinO_led_C_Red, LOW);
    digitalWrite(pinO_led_C_Blu, LOW);
    digitalWrite(pinO_led_C_Grn, LOW);
    for (int i = 0; i < led_LR_Count; i++)
    {
        digitalWrite(pinO_led_L[i], LOW);
        digitalWrite(pinO_led_R[i], LOW);
    }
} // END: off()