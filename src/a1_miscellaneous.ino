//-------------------- Miscellaneous Functions --------------------

// -Set all reset_Key[] array values to 'true' and set all LEDs to 'LOW'
// -Usage: Check if specific reset_Key[#] or randomzier_Key[#] array is 'true', run reset() function
//  and set specific reset_Key[#] array to 'false' to prevent reset() function from looping again
// -Used in select() and patternRandom() functions

void reset()
{

  for (unsigned int i = 0; i < sizeof(reset_Key); i++)
  {
    reset_Key[i] = true;
  }
  for (unsigned int i = 0; i < sizeof(randomizer_Key); i++)
  {
    randomizer_Key[i] = true;
  }
  off();
} // END: reset()

// LEDs are always on, values set to 'HIGH'
void on()
{

  pinO_led_C_Red_Val = HIGH;
  pinO_led_C_Blu_Val = HIGH;
  pinO_led_C_Gre_Val = HIGH;
  digitalWrite(pinO_led_C_Red, pinO_led_C_Red_Val);
  digitalWrite(pinO_led_C_Blu, pinO_led_C_Blu_Val);
  digitalWrite(pinO_led_C_Gre, pinO_led_C_Gre_Val);
  for (int i = 0; i < led_LR_Count; i++)
  {
    pinO_led_L_Val[i] = HIGH;
    pinO_led_R_Val[i] = HIGH;
    digitalWrite(pinO_led_L[i], pinO_led_L_Val[i]);
    digitalWrite(pinO_led_R[i], pinO_led_R_Val[i]);
  }
} // END: on()

// LEDs are always off, values set to 'LOW'
void off()
{

  pinO_led_C_Red_Val = LOW;
  pinO_led_C_Blu_Val = LOW;
  pinO_led_C_Gre_Val = LOW;
  digitalWrite(pinO_led_C_Red, pinO_led_C_Red_Val);
  digitalWrite(pinO_led_C_Blu, pinO_led_C_Blu_Val);
  digitalWrite(pinO_led_C_Gre, pinO_led_C_Gre_Val);
  for (int i = 0; i < led_LR_Count; i++)
  {
    pinO_led_L_Val[i] = LOW;
    pinO_led_R_Val[i] = LOW;
    digitalWrite(pinO_led_L[i], pinO_led_L_Val[i]);
    digitalWrite(pinO_led_R[i], pinO_led_R_Val[i]);
  }
} // END: off()

//-------------------- Pattern Delay Input Filtering --------------------

// Pattern delay calculations with EMA filtering
// -Function requires potentiometer input pin, potentiometer input pin value and a global variable required to remember previous loop values
void patternDelay(int func_pinI_pot, int func_pinI_pot_Val, unsigned long func_Delay_Val_MovAvg)
{

    // Delay variables/values
    unsigned long ms_Current = millis();
    unsigned long ms_Interval = 50;

    // Delay
    if (ms_Current - ms_Previous_Delay >= ms_Interval)
    {
        ms_Previous_Delay = ms_Current;

        // EMA filtering
        // -Set analog read input values
        func_pinI_pot_Val = analogRead(func_pinI_pot);
        // -Calculations
        sample_Average_Delay = (sample_Rate_Delay * func_pinI_pot_Val) + ((1 - sample_Rate_Delay) * sample_Average_Delay);
        // -Saved values required to remember previous loop values
        func_Delay_Val_MovAvg = sample_Average_Delay;

        // Set global delay value
        Delay_Val_MapAvg = func_Delay_Val_MovAvg;
        // -For serial monitor reading output
        pinI_pot_Delay_Val = func_pinI_pot_Val;

        // Delay value mapped to delay potentiometer value with filtering calculations
        Delay_Val_MapAvg = map(func_pinI_pot_Val, 8, 1015, 0, 255);
    }
} // END: patternDelay()