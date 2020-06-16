/*
 * ledPatterns.h - Simple lED patterns
 * Created by Aaron-pd - 14/June/2020
 * Revision #1 - See readMe
 */

#ifndef ledPatterns_h
#define ledPatterns_h

#include "Arduino.h"

class ledPatterns
{

public:
  ledPatterns();

  // Non-pattern functions
  void on();
  void off();

  // Transition pattern functions
  // -These are ran once before repeating patterns
  void transition0();

  // Repeating pattern functions
  // -pot_Pin = Input Pin
  // -pot_Val = Input Pin Value
  // -delay_Val = Pattern Delay Value
  void pattern0(int pot_Pin, int pot_Val, unsigned long delay_Val);
  void pattern1(int pot_Pin, int pot_Val, unsigned long delay_Val);
  void pattern2(int pot_Pin, int pot_Val, unsigned long delay_Val);

private:
  //==========Outputs==========

  // Solid colour LED variables/values
  // Left/Right position based on center tri-colour LED
  // -Pins
  const int _ledPinL[4] = {5, 4, 3, 2};
  const int _ledPinR[4] = {7, 8, 12, 13};
  const int _ledCount = 4;
  // -Pin values
  int _ledPinL_Val[4] = {LOW, LOW, LOW, LOW};
  int _ledPinR_Val[4] = {LOW, LOW, LOW, LOW};

  // Center tri-colour LED variables/values
  // -Pins
  const int _ledPinCRed = 9;
  const int _ledPinCBlue = 10;
  const int _ledPinCGreen = 11;
  // -Pin values
  int _ledPinCRed_Val = LOW;
  int _ledPinCBlue_Val = LOW;
  int _ledPinCGreen_Val = LOW;

  //==========Other==========

  // Delay variables/values
  // -Used by all pattern#() functions
  unsigned long _previousMillis_Pattern = 0;
};

#endif
