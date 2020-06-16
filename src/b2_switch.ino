//-------------------- Functions --------------------

// Control to switch between random pattern/manual pattern selection with 3-way
// switch
void ledSwitch()
{

  // Set analog/digital read input values
  switchPin_PosA_Val = digitalRead(switchPin_PosA);
  switchPin_PosB_Val = digitalRead(switchPin_PosB);

  if (switchPin_PosA_Val == HIGH)
  {
    serialPrint(); /////TEMPORARY: used to turn on/off serialPrint()
  }
}