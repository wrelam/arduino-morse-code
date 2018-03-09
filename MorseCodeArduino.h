/***************************************************************************//**
    @file   MorseCodeArduino.h

    @brief  A class for generating Morse Code on an Arduino
*******************************************************************************/
#ifndef MORSECODEARDUINO_H
#define MORSECODEARDUINO_H

#include "ArduinoSTL.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

/** @brief  An individual Morse Code signal */
typedef enum MorseSignal
{
    DOT = 0,
    DASH
} MorseSignal;

// Convenience macros
#define DIT     DOT
#define DAH     DASH

// Morse Code character mapping
typedef std::map<char, vector<MorseSignal>> MorseCharSet;

/** @brief  Generates Morse Code on an Arduino */
class MorseCodeArduino
{
    private:
        int pin;                /**< Pin for morse code output */
        int timeUnit;           /**< Milliseconds per time unit */
        MorseCharSet charSet;   /**< Morse Code character map */

        /** @brief  Turns on the LED for the given number of milliseconds
         *  @param  onTime  Number of milliseconds to light the LED
         */
        void signal(int onTime);

    public:
        /** @brief  Default MorseCodeArduino constructor
         *  @return Initialized MorseCodeArduino object
         */
        MorseCodeArduino(void);

        /** @brief  Default MorseCodeArduino constructor
         *  @param  led Pin on which signals will be emitted
         *  @return Initialized MorseCodeArduino object
         */
        MorseCodeArduino(int led);

        /** @brief  Default MorseCodeArduino constructor
         *  @param  led         Pin on which signals will be emitted
         *  @param  timeUnit    Number of milliseconds in one time unit
         *  @return Initialized MorseCodeArduino object
         */
        MorseCodeArduino(int led, int timeUnit);

        /** @brief  Default MorseCodeArduino constructor
         *  @param  led         Pin on which signals will be emitted
         *  @param  timeUnit    Number of milliseconds in one time unit
         *  @param  set         MorseCodeCharSet to be used
         *  @return Initialized MorseCodeArduino object
         */
        MorseCodeArduino(int led, int timeUnit, MorseCharSet set);

        /** @brief  Emits a dot signal */
        void dot(void);

        /** @brief  Emits a dash signal */
        void dash(void);

        /** @brief  Transmits a vector of raw morse code signals
         *  @param  &signals    Vector of raw morse code signals to be
         *                      transmitted
         */
        void txRaw(const vector<MorseSignal>& signals);

        /** @brief  Transmits a letter with Morse Code
         *  @param  &l  Letter to be transmitted
         */
        void txLetter(const char& c);

        /** @brief  Transmits a string as a word with Morse Code
         *  @param  &w  Word to be transmitted
         */
        void txWord(const string& s);

        /** @brief  Transmits a character array as a word with Morse Code
         *  @param  *w  Word to be transmitted
         */
        void txWord(const char * const s);
};

#endif /* MORSECODEARDUINO_H */

