//-------------------- Functions --------------------

// Set all of patternReset[] array to 'true' and set all LEDs to 'LOW'
// Usage: Check if specific patternReset[#] array is 'true', run patternReset()
// function, set specific patternReset[#] array to 'false' to prevent
// patternReset() function from running agian (see ledSelect() function)

void reset()
{

  for (int i = 0; i < patternResetCount; i++)
  {
    patternReset[i] = true;
  }
  ledPatterns.off();
} // END: function
