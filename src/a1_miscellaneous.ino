//-------------------- Miscellaneous Functions --------------------

// -Set all reset_Key[] array values to 'true' and set all LEDs to 'LOW'
// -Usage: Check if specific reset_Key[#] array is 'true', run reset() function and
//  set specific reset_Key[#] array to 'false' to prevent reset() function from looping
// -Used in select() function

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