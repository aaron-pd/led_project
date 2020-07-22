//-------------------- Transition Pattern Functions --------------------

//==========Class==========

// Base Class
class Transition
{
public:
    virtual void transition() = 0;
}; // END: Transition

//==========Derived==========

// Derived 1 : Transition
// Transition LED pattern 0
// -Fade through LEDs outwards from the center
class Transition1 : public Transition
{
public:
    void transition()
    {

        digitalWrite(pinO_led_L[0], HIGH);
        digitalWrite(pinO_led_R[0], HIGH);

        for (int i = 0; i < led_LR_Count; i++)
        {
            digitalWrite(pinO_led_L[i - 1], LOW);
            digitalWrite(pinO_led_R[i - 1], LOW);
            digitalWrite(pinO_led_L[i], HIGH);
            digitalWrite(pinO_led_R[i], HIGH);
            delay(transition_Delay);
        }
        digitalWrite(pinO_led_L[3], LOW);
        digitalWrite(pinO_led_R[3], LOW);
        delay(transition_Delay);
        off();
    };
}; // END: transition() : Transition1

// Derived 2 : Transition
// Transition LED pattern 1
// -Fade through LEDs outwards from the center, with one LED following
class Transition2 : public Transition
{
public:
    void transition()
    {

        digitalWrite(pinO_led_L[0], HIGH);
        digitalWrite(pinO_led_R[0], HIGH);
        delay(transition_Delay);
        for (int i = 0; i < (led_LR_Count - 1); i++)
        {
            digitalWrite(pinO_led_L[i - 1], LOW);
            digitalWrite(pinO_led_R[i - 1], LOW);
            digitalWrite(pinO_led_L[i + 1], HIGH);
            digitalWrite(pinO_led_R[i + 1], HIGH);
            delay(transition_Delay);
        }
        digitalWrite(pinO_led_L[2], LOW);
        digitalWrite(pinO_led_R[2], LOW);
        delay(transition_Delay);
        digitalWrite(pinO_led_L[3], LOW);
        digitalWrite(pinO_led_R[3], LOW);
        delay(transition_Delay);
        off();
    };
}; // END: transition() : Transition2

// Derived 3 : Transition
// Transition LED pattern 2
// -Turn on two sets of LEDs at a time until all LEDs are on
class Transition3 : public Transition
{
public:
    void transition()
    {

        digitalWrite(pinO_led_L[0], HIGH);
        digitalWrite(pinO_led_L[1], HIGH);
        delay(transition_Delay);
        digitalWrite(pinO_led_R[0], HIGH);
        digitalWrite(pinO_led_R[1], HIGH);
        delay(transition_Delay);
        digitalWrite(pinO_led_L[2], HIGH);
        digitalWrite(pinO_led_L[3], HIGH);
        delay(transition_Delay);
        digitalWrite(pinO_led_R[2], HIGH);
        digitalWrite(pinO_led_R[3], HIGH);
        delay(transition_Delay);
        off();
    };
}; // END: transition() : Transition3

//-------------------- Transition Randomizer --------------------

// Randomly play a transition pattern
void transitionRandom()
{

    // Transition object declarations
    Transition1 tra1;
    Transition2 tra2;
    Transition3 tra3;
    Transition *tra[] = {&tra1, &tra2, &tra3};

    // Run random transition
    tra[random(1, 3)]->transition();
} // END: transitionRandom()