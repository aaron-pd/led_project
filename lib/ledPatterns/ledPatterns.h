/*
 * ledPatterns.h - Simple lED patterns
 * Created by Aaron-pd - 14/June/2020
 * Revision #1 - See readMe
 */

//==========Define==========

#ifndef ledPatterns_h
#define ledPatterns_h

//==========Include==========

#include "Arduino.h"

//==========Class==========

class ledPatterns
{

  //==========Public==========
public:
  ledPatterns();

  //----------Other----------

  // Random seed input variables/values
  int seedPin;

  //----------Non-pattern functions----------

  // These turn all LEDs to always on/always off
  void on();
  void off();

  //----------Transition pattern functions----------

  // These are ran once before repeating patterns
  void transition0();
  void transition1();
  void transition2();

  // Randomizer transition function
  void transitionRND();
  // -Typedef for class function
  typedef void (ledPatterns::*transitionFn)();
  // -Array of function pointers
  ledPatterns::transitionFn transitionArray[3] =
      {
          &ledPatterns::transition0,
          &ledPatterns::transition1,
          &ledPatterns::transition2,
  };

  //----------Repeating pattern functions----------

  // These continuously play a pattern
  // -pot_Pin = Input Pin
  // -pot_Val = Input Pin Value
  // -delay_Val = Pattern Delay Value
  void pattern0(int pot_Pin, int pot_Val, unsigned long delay_Val);
  void pattern1(int pot_Pin, int pot_Val, unsigned long delay_Val);
  void pattern2(int pot_Pin, int pot_Val, unsigned long delay_Val);

  // Randomizer pattern function
  void patternRND(int pot_Pin, int pot_Val, unsigned long delay_Val);
  // -Typedef for class function
  typedef void (ledPatterns::*patternFn)(int pot_Pin, int pot_Val, unsigned long delay_Val);
  // -Array of function pointers
  ledPatterns::patternFn patternArray[3] =
      {
          &ledPatterns::pattern0,
          &ledPatterns::pattern1,
          &ledPatterns::pattern2,
  };

  //==========Private==========

private:
  //----------Outputs----------

  // Solid colour LED variables/values
  // Left/Right position based on center tri-colour LED
  // -Pins
  // --Outputs
  const int _ledPinL[4] = {5, 4, 3, 2};
  const int _ledPinR[4] = {7, 8, 12, 13};
  const int _ledCount = 4;
  // -Pin values
  // --Outputs
  int _ledPinL_Val[4] = {LOW, LOW, LOW, LOW};
  int _ledPinR_Val[4] = {LOW, LOW, LOW, LOW};

  // Center tri-colour LED variables/values
  // -Pins
  // --Outputs
  const int _ledPinCRed = 9;
  const int _ledPinCBlue = 10;
  const int _ledPinCGreen = 11;
  // -Pin values
  // --Outputs
  int _ledPinCRed_Val = LOW;
  int _ledPinCBlue_Val = LOW;
  int _ledPinCGreen_Val = LOW;

  //----------Other----------

  // Delay variables/values
  // -Used by all pattern#() functions
  unsigned long _previousMillis_Pattern = 0;
  // -Used by all transition#() functions
  int _dTime = 200;
};

#endif
