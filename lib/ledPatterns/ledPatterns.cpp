/*
 * ledPatterns.cpp - Simple lED patterns
 * Created by Aaron-pd - 14/June/2020
 * Revision #1 - See readMe
 */

//==========Includes==========
#include "ledPatterns.h"
#include "Arduino.h"
#include "stdlib.h"

//-------------------- Class Initialization: ledPatterns --------------------

ledPatterns::ledPatterns()
{

  // LED pin setup
  // Left/Right solid colour LED sets
  for (int i = 0; i < _ledCount; i++)
  {
    pinMode(_ledPinL[i], OUTPUT);
    pinMode(_ledPinR[i], OUTPUT);
  }
  // Center tri-colour LED
  pinMode(_ledPinCRed, OUTPUT);
  pinMode(_ledPinCBlue, OUTPUT);
  pinMode(_ledPinCGreen, OUTPUT);

  // Randomizer seed
  // -Based on unused analog input pin
  randomSeed(analogRead(seedPin));
}

//-------------------- Non-Pattern Functions --------------------

// LEDs are always on
void ledPatterns::on()
{

  _ledPinCRed_Val = HIGH;
  _ledPinCBlue_Val = HIGH;
  _ledPinCGreen_Val = HIGH;
  digitalWrite(_ledPinCRed, _ledPinCRed_Val);
  digitalWrite(_ledPinCBlue, _ledPinCBlue_Val);
  digitalWrite(_ledPinCGreen, _ledPinCGreen_Val);
  for (int i = 0; i < _ledCount; i++)
  {
    _ledPinL_Val[i] = HIGH;
    _ledPinR_Val[i] = HIGH;
    digitalWrite(_ledPinL[i], _ledPinL_Val[i]);
    digitalWrite(_ledPinR[i], _ledPinR_Val[i]);
  }
}

// LEDs are always off
void ledPatterns::off()
{

  _ledPinCRed_Val = LOW;
  _ledPinCBlue_Val = LOW;
  _ledPinCGreen_Val = LOW;
  digitalWrite(_ledPinCRed, _ledPinCRed_Val);
  digitalWrite(_ledPinCBlue, _ledPinCBlue_Val);
  digitalWrite(_ledPinCGreen, _ledPinCGreen_Val);
  for (int i = 0; i < _ledCount; i++)
  {
    _ledPinL_Val[i] = LOW;
    _ledPinR_Val[i] = LOW;
    digitalWrite(_ledPinL[i], _ledPinL_Val[i]);
    digitalWrite(_ledPinR[i], _ledPinR_Val[i]);
  }
}

//-------------------- Transition Patterns --------------------

//==========Transition Randomizer==========

// Transition function
// -Randomly select a transition function
void ledPatterns::transitionRND()
{

  // Random number selection
  int r = random(3);
  // Assign variable 'transitionFn' to a new variable 'fn' with a random array number
  ledPatterns::transitionFn fn = ledPatterns::transitionArray[r];
  // Assign 'ledPatterns' class to variable 'display'
  ledPatterns display;
  // Call randomly selected function
  (display.*fn)();
}

//==========Transition0==========

// Transition LED pattern 0
// -Fade through LEDs outwards from the center
void ledPatterns::transition0()
{

  digitalWrite(_ledPinL[0], HIGH);
  digitalWrite(_ledPinR[0], HIGH);

  for (int i = 0; i < _ledCount; i++)
  {
    digitalWrite(_ledPinL[i - 1], LOW);
    digitalWrite(_ledPinR[i - 1], LOW);
    digitalWrite(_ledPinL[i], HIGH);
    digitalWrite(_ledPinR[i], HIGH);
    delay(_dTime);
  }
  digitalWrite(_ledPinL[3], LOW);
  digitalWrite(_ledPinR[3], LOW);
  delay(_dTime);
}

// Transition LED pattern 1
// -Fade through LEDs outwards from the center, with one LED following
void ledPatterns::transition1()
{

  digitalWrite(_ledPinL[0], HIGH);
  digitalWrite(_ledPinR[0], HIGH);
  delay(_dTime);
  for (int i = 0; i < (_ledCount - 1); i++)
  {
    digitalWrite(_ledPinL[i - 1], LOW);
    digitalWrite(_ledPinR[i - 1], LOW);
    digitalWrite(_ledPinL[i + 1], HIGH);
    digitalWrite(_ledPinR[i + 1], HIGH);
    delay(_dTime);
  }
  digitalWrite(_ledPinL[2], LOW);
  digitalWrite(_ledPinR[2], LOW);
  delay(_dTime);
  digitalWrite(_ledPinL[3], LOW);
  digitalWrite(_ledPinR[3], LOW);
  delay(_dTime);
  ledPatterns::off();
}

// Transition LED pattern 2
// -Turn on two sets of LEDs at a time until all LEDs are on
void ledPatterns::transition2()
{

  digitalWrite(_ledPinL[0], HIGH);
  digitalWrite(_ledPinL[1], HIGH);
  delay(_dTime);
  digitalWrite(_ledPinR[0], HIGH);
  digitalWrite(_ledPinR[1], HIGH);
  delay(_dTime);
  digitalWrite(_ledPinL[2], HIGH);
  digitalWrite(_ledPinL[3], HIGH);
  delay(_dTime);
  digitalWrite(_ledPinR[2], HIGH);
  digitalWrite(_ledPinR[3], HIGH);
  delay(_dTime);
  ledPatterns::off();
}

//-------------------- Repeating Pattern Functions --------------------

//==========Delay EMA Smoothing==========

// Reduces input signal noise for variable delay value
void ledPatterns::patternDelay(int pot_Pin, int pot_Val, unsigned long delay_Val_EMA)
{

  // Delay variables/values
  unsigned long currentMillis = millis();
  unsigned long intervalMillis = 50;

  // EMA Smoothing setup
  _sampleAverage_Delay = analogRead(pot_Pin);

  // Delay
  if (currentMillis - _previousMillis_Delay >= intervalMillis)
  {
    _previousMillis_Delay = currentMillis;

    // EMA smoothing
    // -Set analog read input values
    pot_Val = analogRead(pot_Pin);
    // -calculations
    _sampleAverage_Delay =
        (_sampleRate_Delay * pot_Val) + ((1 - _sampleRate_Delay) * _sampleAverage_Delay);
    // Delay value set by delay potentiometer with Smoothing calculations
    delay_Val_EMA = _sampleAverage_Delay;
    delay_Val_EMA = map(pot_Val, 8, 1015, 0, 255);
    // Set value for global variable
    delay_Val_AVG = delay_Val_EMA;
  }
}

//==========Pattern Randomizer==========

// Transition function
// -Randomly select a pattern function
void ledPatterns::patternRND(unsigned long delay_Val)
{

  // Random number selection
  int r = random(3);
  // Assign variable 'patternFn' to a new variable 'fn' with a random array number
  ledPatterns::patternFn fn = ledPatterns::patternArray[r];
  // Assign 'ledPatterns' class to variable 'display'
  ledPatterns display;
  // Cycle pattern 10 times
  for (int i = 0; i < 10; i++)
  {
    // Call randomly selected function
    (display.*fn)(delay_Val);
  }
}

//==========Pattern0==========

// Sets LED pattern, delay based on variable delay value
// -Pattern will flash all LEDs simultaneously
// -delay_Val = user custom value or smoothed input variable 'delay_Val_AVG' from 'ledPatterns::patternRND' function
void ledPatterns::pattern0(unsigned long delay_Val)
{

  // Delay variables/values
  unsigned long currentMillis = millis();

  // Delay
  if (currentMillis - _previousMillis_Pattern >= delay_Val)
  {
    _previousMillis_Pattern = currentMillis;

    // LED pattern
    if (_ledPinCRed_Val == LOW && _ledPinCBlue_Val == LOW &&
        _ledPinCGreen_Val == LOW)
    {
      _ledPinCRed_Val = HIGH;
      _ledPinCBlue_Val = HIGH;
      _ledPinCGreen_Val = HIGH;
      for (int i = 0; i < _ledCount; i++)
      {
        if (_ledPinL_Val[i] == LOW && _ledPinR_Val[i] == LOW)
        {
          _ledPinL_Val[i] = HIGH;
          _ledPinR_Val[i] = HIGH;
        }
      }
    }
    else
    {
      _ledPinCRed_Val = LOW;
      _ledPinCBlue_Val = LOW;
      _ledPinCGreen_Val = LOW;
      for (int i = 0; i < _ledCount; i++)
      {
        if (_ledPinL_Val[i] == HIGH && _ledPinR_Val[i] == HIGH)
        {
          _ledPinL_Val[i] = LOW;
          _ledPinR_Val[i] = LOW;
        }
      }
    }
  }

  // Display LEDs based on values from previous if/else statement
  digitalWrite(_ledPinCRed, _ledPinCRed_Val);
  digitalWrite(_ledPinCBlue, _ledPinCBlue_Val);
  digitalWrite(_ledPinCGreen, _ledPinCGreen_Val);
  for (int i = 0; i < _ledCount; i++)
  {
    digitalWrite(_ledPinL[i], _ledPinL_Val[i]);
    digitalWrite(_ledPinR[i], _ledPinR_Val[i]);
  }
}

//==========Pattern1==========

// Sets LED pattern, delay based on variable delay value
// -Pattern will flash center LED, then fade through the following LEDs outwards
void ledPatterns::pattern1(unsigned long delay_Val)
{

  // Delay variables/values
  unsigned long currentMillis = millis();

  // Delay
  if (currentMillis - _previousMillis_Pattern >= delay_Val)
  {
    _previousMillis_Pattern = currentMillis;

    // LED pattern
    if (_ledPinCRed_Val == LOW && _ledPinCBlue_Val == LOW &&
        _ledPinCGreen_Val == LOW)
    {
      _ledPinCRed_Val = HIGH;
      _ledPinCBlue_Val = HIGH;
      _ledPinCGreen_Val = HIGH;
      digitalWrite(_ledPinCRed, _ledPinCRed_Val);
      digitalWrite(_ledPinCBlue, _ledPinCBlue_Val);
      digitalWrite(_ledPinCGreen, _ledPinCGreen_Val);
      for (int i = 0; i < _ledCount; i++)
      {
        digitalWrite(_ledPinL[i], LOW);
        digitalWrite(_ledPinR[i], LOW);
      }
    }
    else
    {
      _ledPinCRed_Val = LOW;
      _ledPinCBlue_Val = LOW;
      _ledPinCGreen_Val = LOW;
      digitalWrite(_ledPinCRed, _ledPinCRed_Val);
      digitalWrite(_ledPinCBlue, _ledPinCBlue_Val);
      digitalWrite(_ledPinCGreen, _ledPinCGreen_Val);
      for (int i = 0; i < _ledCount; i++)
      {
        digitalWrite(_ledPinL[i], HIGH);
        digitalWrite(_ledPinR[i], HIGH);
        delay(50);
        digitalWrite(_ledPinL[i], LOW);
        digitalWrite(_ledPinR[i], LOW);
      }
    }
  }
}

//==========Pattern2==========

// Sets LED pattern, delay based on variable delay value
// -Pattern will flash center LED, then fade through the following LEDs outwards,
//  center LED flashes through each colour
void ledPatterns::pattern2(unsigned long delay_Val)
{

  // Delay variables/values
  unsigned long currentMillis = millis();

  // Delay
  if (currentMillis - _previousMillis_Pattern >= delay_Val)
  {
    _previousMillis_Pattern = currentMillis;

    // LED pattern
    if (_ledPinCRed_Val == LOW && _ledPinCBlue_Val == LOW &&
        _ledPinCGreen_Val == LOW)
    {
      _ledPinCRed_Val = HIGH;
      _ledPinCBlue_Val = HIGH;
      _ledPinCGreen_Val = HIGH;
      digitalWrite(_ledPinCRed, _ledPinCRed_Val);
      digitalWrite(_ledPinCBlue, _ledPinCBlue_Val);
      digitalWrite(_ledPinCGreen, _ledPinCGreen_Val);
      for (int i = 0; i < _ledCount; i++)
      {
        digitalWrite(_ledPinL[i], LOW);
        digitalWrite(_ledPinR[i], LOW);
      }
    }
    else
    {
      _ledPinCRed_Val = LOW;
      _ledPinCBlue_Val = LOW;
      _ledPinCGreen_Val = LOW;
      digitalWrite(_ledPinCRed, HIGH);
      digitalWrite(_ledPinCBlue, LOW);
      digitalWrite(_ledPinCGreen, LOW);
      digitalWrite(_ledPinL[0], HIGH);
      digitalWrite(_ledPinR[0], HIGH);
      delay(50);
      digitalWrite(_ledPinCRed, HIGH);
      digitalWrite(_ledPinCBlue, LOW);
      digitalWrite(_ledPinCGreen, HIGH);
      digitalWrite(_ledPinL[0], LOW);
      digitalWrite(_ledPinR[0], LOW);
      digitalWrite(_ledPinL[1], HIGH);
      digitalWrite(_ledPinR[1], HIGH);
      delay(50);
      digitalWrite(_ledPinCRed, LOW);
      digitalWrite(_ledPinCBlue, HIGH);
      digitalWrite(_ledPinCGreen, LOW);
      digitalWrite(_ledPinL[1], LOW);
      digitalWrite(_ledPinR[1], LOW);
      digitalWrite(_ledPinL[2], HIGH);
      digitalWrite(_ledPinR[2], HIGH);
      delay(50);
      digitalWrite(_ledPinCRed, LOW);
      digitalWrite(_ledPinCBlue, LOW);
      digitalWrite(_ledPinCGreen, HIGH);
      digitalWrite(_ledPinL[2], LOW);
      digitalWrite(_ledPinR[2], LOW);
      digitalWrite(_ledPinL[3], HIGH);
      digitalWrite(_ledPinR[3], HIGH);
      delay(50);
      digitalWrite(_ledPinCRed, LOW);
      digitalWrite(_ledPinCBlue, LOW);
      digitalWrite(_ledPinCGreen, LOW);
      digitalWrite(_ledPinL[3], LOW);
      digitalWrite(_ledPinR[3], LOW);
      delay(50);
    }
  }
}