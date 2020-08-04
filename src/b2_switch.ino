//-------------------- Input Functions --------------------

// Control to switch between random pattern/manual pattern selection with 3-way switch
void switch_AB()
{

  // Set digital read switch input values
  pinI_switch_PosA_Val = digitalRead(pinI_switch_PosA);
  pinI_switch_PosB_Val = digitalRead(pinI_switch_PosB);

  // Switch position 'A'
  // -Play all patterns randomly
  if (pinI_switch_PosA_Val == HIGH)
  {
    while (switch_PosA_Key == true)
    {
      reset();
      switch_PosA_Key = false;
      switch_PosB_Key = true;
    }
    patternRandom();
  } // END: if

  // Switch position 'B'
  // -Play selected patterns only
  else if (pinI_switch_PosB_Val == HIGH)
  {
    while (switch_PosB_Key == true)
    {
      reset();
      switch_PosA_Key = true;
      switch_PosB_Key = false;
    }
    select();
  } // END: if

  // Turn all LEDs off if switch state is undetermined
  // -Bug avoidance code
  else
  {
    off();
    switch_PosA_Key = true;
    switch_PosB_Key = true;
  } // END: else
} // END: switch_AB()
