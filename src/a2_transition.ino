//-------------------- Transition Patterns Functions --------------------

//==========Classes==========

// Base Class
class Transition
{
public:
    virtual void transition() = 0;
};

// Derived Class 1
// Transition LED pattern 0
// -Fade through LEDs outwards from the center
class Transition1 : public Transition
{
public:
    void transition()
    {

        digitalWrite(ledPinL[0], HIGH);
        digitalWrite(ledPinR[0], HIGH);

        for (int i = 0; i < ledCount; i++)
        {
            digitalWrite(ledPinL[i - 1], LOW);
            digitalWrite(ledPinR[i - 1], LOW);
            digitalWrite(ledPinL[i], HIGH);
            digitalWrite(ledPinR[i], HIGH);
            delay(dTime);
        }
        digitalWrite(ledPinL[3], LOW);
        digitalWrite(ledPinR[3], LOW);
        delay(dTime);
        off();
    };
}; // END: transition1

// Derived Class 2
// Transition LED pattern 1
// -Fade through LEDs outwards from the center, with one LED following
class Transition2 : public Transition
{
public:
    void transition()
    {

        digitalWrite(ledPinL[0], HIGH);
        digitalWrite(ledPinR[0], HIGH);
        delay(dTime);
        for (int i = 0; i < (ledCount - 1); i++)
        {
            digitalWrite(ledPinL[i - 1], LOW);
            digitalWrite(ledPinR[i - 1], LOW);
            digitalWrite(ledPinL[i + 1], HIGH);
            digitalWrite(ledPinR[i + 1], HIGH);
            delay(dTime);
        }
        digitalWrite(ledPinL[2], LOW);
        digitalWrite(ledPinR[2], LOW);
        delay(dTime);
        digitalWrite(ledPinL[3], LOW);
        digitalWrite(ledPinR[3], LOW);
        delay(dTime);
        off();
    };
}; // END: transition2

// Derived Class 3
// Transition LED pattern 2
// -Turn on two sets of LEDs at a time until all LEDs are on
class Transition3 : public Transition
{
public:
    void transition()
    {

        digitalWrite(ledPinL[0], HIGH);
        digitalWrite(ledPinL[1], HIGH);
        delay(dTime);
        digitalWrite(ledPinR[0], HIGH);
        digitalWrite(ledPinR[1], HIGH);
        delay(dTime);
        digitalWrite(ledPinL[2], HIGH);
        digitalWrite(ledPinL[3], HIGH);
        delay(dTime);
        digitalWrite(ledPinR[2], HIGH);
        digitalWrite(ledPinR[3], HIGH);
        delay(dTime);
        off();
    };
}; // END: transition3

//==========Transition Randomizer==========

// Randomly play a transition pattern
void transitionRandom()
{

    // Transition function object declarations
    Transition1 tra1;
    Transition2 tra2;
    Transition3 tra3;
    Transition *tra[] = {&tra1, &tra2, &tra3};

    // Run transition
    tra[random(3)]->transition();
} // END: transitionRandom