/*
 * ledPatterns.cpp - Simple lED patterns
 * Created by Aaron-pd - 14/June/2020
 * Revision #1 - See readMe
 */

#include "ledPatterns.h"
#include "Arduino.h"

//-------------------- Initialization --------------------

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

//==========Transition0==========

// Transition LED pattern 0
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
    delay(100);
  }
  digitalWrite(_ledPinL[3], LOW);
  digitalWrite(_ledPinR[3], LOW);
  delay(100);
}

//-------------------- Repeating Pattern Functions --------------------

//==========Pattern0==========

// Sets LED pattern, delay based on variable delay value
// -Pattern will flash all LEDs simultaneously
void ledPatterns::pattern0(int pot_Pin, int pot_Val, unsigned long delay_Val)
{

  // Delay Rate                                /////REVIEW: EMA Smoothing?
  // -Set analog/digital read input values
  pot_Val = analogRead(pot_Pin);
  // -Delay rate value mapped to input potentiometer
  delay_Val = map(pot_Val, 8, 1015, 0, 999);

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
void ledPatterns::pattern1(int pot_Pin, int pot_Val, unsigned long delay_Val)
{

  // Delay Rate                                /////REVIEW: EMA Smoothing?
  // -Set analog/digital read input values
  pot_Val = analogRead(pot_Pin);
  // -Delay rate value mapped to input potentiometer
  delay_Val = map(pot_Val, 8, 1015, 0, 999);
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
// -Pattern will flash center LED, then fade through the following LEDs outwards
// while the center LED matches each colour currently lit
void ledPatterns::pattern2(int pot_Pin, int pot_Val, unsigned long delay_Val)
{
  // Delay Rate                                /////REVIEW: EMA Smoothing?
  // -Set analog/digital read input values
  pot_Val = analogRead(pot_Pin);
  // -Delay rate value mapped to input potentiometer
  delay_Val = map(pot_Val, 8, 1015, 0, 999);
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