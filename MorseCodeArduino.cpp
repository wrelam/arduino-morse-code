/***************************************************************************//**
    @file   MorseCodeArduino.cpp

    @brief  Class definition for MorseCodeArduino
*******************************************************************************/
#include "Arduino.h"
#include "MorseCodeArduino.h"
#include <vector>

using namespace std;

/* International Morse Code as specified in ITU-R M.1677-1 10/2009 */
MorseCharSet IntSet {
    /*  1.1.1   Letters */
    {'a',   { DOT, DASH } },
    {'b',   { DASH, DOT, DOT, DOT } },
    {'c',   { DASH, DOT, DASH, DOT } },
    {'d',   { DASH, DOT, DOT } },
    {'e',   { DOT } },
    {'é',   { DOT, DOT, DASH, DOT, DOT } },
    {'f',   { DOT, DOT, DASH, DOT } },
    {'g',   { DASH, DASH, DOT } },
    {'h',   { DOT, DOT, DOT, DOT } },
    {'i',   { DOT, DOT } },
    {'j',   { DOT, DASH, DASH, DASH } },
    {'k',   { DASH, DOT, DASH } },
    {'l',   { DOT, DASH, DOT, DOT } },
    {'m',   { DASH, DASH } },
    {'n',   { DASH, DOT } },
    {'o',   { DASH, DASH, DASH } },
    {'p',   { DOT, DASH, DASH, DOT } },
    {'q',   { DASH, DASH, DOT, DASH } },
    {'r',   { DOT, DASH, DOT } },
    {'s',   { DOT, DOT, DOT } },
    {'t',   { DASH } },
    {'u',   { DOT, DOT, DASH } },
    {'v',   { DOT, DOT, DOT, DASH } },
    {'w',   { DOT, DASH, DASH } },
    {'x',   { DASH, DOT, DOT, DASH } },
    {'y',   { DASH, DOT, DASH, DASH } },
    {'z',   { DASH, DASH, DOT, DOT } },

    /*  1.1.2   Figures */
    {'1',   { DOT, DASH, DASH, DASH, DASH } },
    {'2',   { DOT, DOT, DASH, DASH, DASH } },
    {'3',   { DOT, DOT, DOT, DASH, DASH } },
    {'4',   { DOT, DOT, DOT, DOT, DASH } },
    {'5',   { DOT, DOT, DOT, DOT, DOT } },
    {'6',   { DASH, DOT, DOT, DOT, DOT } },
    {'7',   { DASH, DASH, DOT, DOT, DOT } },
    {'8',   { DASH, DASH, DASH, DOT, DOT } },
    {'9',   { DASH, DASH, DASH, DASH, DOT } },
    {'0',   { DASH, DASH, DASH, DASH, DASH } },

    /*  1.1.3   Punctuation marks and miscellaneous signs */
    {'.',   { DOT, DASH, DOT, DASH, DOT, DASH } },
    {',',   { DASH, DASH, DOT, DOT, DASH, DASH } },
    {':',   { DASH, DASH, DASH, DOT, DOT, DOT } },
    {'?',   { DOT, DOT, DASH, DASH, DOT, DOT } },
    {'\'',  { DOT, DASH, DASH, DASH, DASH, DOT } },
    {'-',   { DASH, DOT, DOT, DOT, DOT, DASH } },
    {'/',   { DASH, DOT, DOT, DASH, DOT } },
    {'(',   { DASH, DOT, DASH, DASH, DOT } },
    {')',   { DASH, DOT, DASH, DASH, DOT, DASH } },
    {'\"',  { DOT, DASH, DOT, DOT, DASH, DOT } },
    {'=',   { DASH, DOT, DOT, DOT, DASH } },
    {'+',   { DOT, DASH, DOT, DASH, DOT } },
    {'@',   { DOT, DASH, DASH, DOT, DASH, DOT } },


    /*  3.3     Percentage or per thousand sign */
    /*  3.3.1   To indicate the signal % or 0/00, the figure 0, the fraction bar,
     *          and the figures 0 or 00 shall be transmitted successfully (i.e. 0/0,
     *          0/00).
     */
    {'%',   { DASH, DASH, DASH, DASH, DASH,
              DASH, DOT, DOT, DASH, DOT,
              DASH, DASH, DASH, DASH, DASH } },
};

/*******************************************************************************
    MorseCodeArduino
*//**
    @brief  Default MorseCodeArduino constructor

    @return Initialized MorseCodeArduino object
*******************************************************************************/
MorseCodeArduino::MorseCodeArduino(void) :
    pin{LED_BUILTIN}, timeUnit(1000), charSet(IntSet)
{}


/*******************************************************************************
    MorseCodeArduino
*//**
    @brief  MorseCodeArduino constructor
    @param  led Pin on which signals will be emitted

    @return Initialized MorseCodeArduino object
*******************************************************************************/
MorseCodeArduino::MorseCodeArduino(int led) :
    pin{led}, timeUnit(1000), charSet(IntSet)
{}


/*******************************************************************************
    MorseCodeArduino
*//**
    @brief  MorseCodeArduino constructor
    @param  led         Pin on which signals will be emitted
    @param  timeUnit    Number of milliseconds in one time unit

    @return Initialized MorseCodeArduino object
*******************************************************************************/
MorseCodeArduino::MorseCodeArduino(int led, int timeUnit) :
    pin{led}, timeUnit{timeUnit}, charSet(IntSet)
{}


/*******************************************************************************
    MorseCodeArduino
*//**
    @brief  MorseCodeArduino constructor
    @param  led         Pin on which signals will be emitted
    @param  timeUnit    Number of milliseconds in one time unit
    @param  set         MorseCodeCharSet to be used

    @return Initialized MorseCodeArduino object
*******************************************************************************/
MorseCodeArduino::MorseCodeArduino(int led, int timeUnit, MorseCharSet set) :
    pin{led}, timeUnit{timeUnit}, charSet(set)
{}


/*******************************************************************************
    signal
*//**
    @brief  Lights the LED for a given number of milliseconds
    @param  onTime  Number of milliseconds to light the LED
*******************************************************************************/
void
MorseCodeArduino::signal(int onTime)
{
    digitalWrite(pin, HIGH);
    delay(onTime);
    digitalWrite(pin, LOW);
    delay(timeUnit);
}


/*******************************************************************************
    dot
*//**
    @brief  Emits a dot signal
*******************************************************************************/
void
MorseCodeArduino::dot(void)
{
    signal(timeUnit);
}


/*******************************************************************************
    dash
*//**
    @brief  Emits a dash signal
*******************************************************************************/
void
MorseCodeArduino::dash(void)
{
    signal(3 * timeUnit);
}


/*******************************************************************************
    txRaw
*//**
    @brief  Transmits a vector of raw morse code signals
    @param  &signals    Vector of raw morse code signals to be transmitted
*******************************************************************************/
void
MorseCodeArduino::txRaw(const vector<MorseSignal>& signals)
{
    for (const auto& s : signals)
    {
        switch (s)
        {
        case DOT:
            dot();
            break;

        case DASH:
            dash();
            break;

        default:
            break;
        }
    }
}


/*******************************************************************************
    txLetter
*//**
    @brief  Transmits a letter with Morse Code
    @param  &l  Letter to be transmitted
*******************************************************************************/
void
MorseCodeArduino::txLetter(const char& l)
{
    txRaw(charSet[tolower(l)]);
}


/*******************************************************************************
    txWord
*//**
    @brief  Transmits a string as a word with Morse Code
    @param  &w  Word to be transmitted
*******************************************************************************/
void
MorseCodeArduino::txWord(const string& w)
{
    for (const auto& l : w)
    {
        txLetter(l);
        /*  3 = 2 + the timeUnit from the signal itself */
        delay(2 * timeUnit);
    }
    /* 7 = 4 + 3 timeUnits from the last character */
    delay(4 * timeUnit);
}


/*******************************************************************************
    txWord
*//**
    @brief  Transmits a character array as a word with Morse Code
    @param  *w  Word to be transmitted
*******************************************************************************/
void
MorseCodeArduino::txWord(const char * const w)
{
    size_t i = 0;

    for (i = 0; i < strlen(w); i++)
    {
        txLetter(w[i]);
        /*  3 = 2 + the timeUnit from the signal itself */
        delay(2 * timeUnit);
    }
    /* 7 = 4 + 3 timeUnits from the last character */
    delay(4 * timeUnit);
}

