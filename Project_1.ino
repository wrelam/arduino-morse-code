/***************************************************************************//**
    @file   Project_1.ino

    @brief  Emits Morse Code on an Arduino board
    @author Walt Elam
*******************************************************************************/
#include "ArduinoSTL.h"
#include "Keyboard.h"
#include "MorseCodeArduino.h"

#include <vector>
using namespace std;

// Digital pin used for status indications
#define DBG_LED     (11)
// Digital pin used for Morse Code signaling
#define MORSE_LED   (12)
// Sentinel character to restart the main loop
#define SENTINEL    '#'

/*******************************************************************************
    setup
*//**
    @brief  Initializes the serial input interface
*******************************************************************************/
void
setup(void)
{
    Serial.begin(9600);
    while (!Serial)
    {
        // Wait until it's connected
    }
}


/*******************************************************************************
    eatInput
*//**
    @brief  Retrieves and ignores any remaining serial input
*******************************************************************************/
static void
eatInput(void)
{
    while (0 < Serial.available())
    {
        Serial.read();
    }
}


/*******************************************************************************
    loop
*//**
    @brief  Waits for input, emits it as Morse Code, and iterates after
            receiving the sentinal
*******************************************************************************/
void
loop(void)
{
    MorseCodeArduino mc(MORSE_LED);
    char c = 0;
    char buf[BUFSIZ] = { 0 };
    size_t i = 0;

    // Indicate the Arduino is ready for input
    digitalWrite(DBG_LED, HIGH);

    // Wait for input
    while (0 >= Serial.available())
    {
        // Do nothing
    }

    // Gather input
    i = Serial.readBytesUntil('\n', buf, sizeof(buf) - 1);

    // Indicate input was received
    digitalWrite(DBG_LED, LOW);
    delay(1000);
    digitalWrite(DBG_LED, HIGH);
    delay(1000);
    digitalWrite(DBG_LED, LOW);
    delay(1000);

    // Emit characters as morse code
    mc.txWord(buf);

    eatInput();

    // Wait for sentinel
    while (1)
    {
        digitalWrite(DBG_LED, HIGH);
        delay(100);
        digitalWrite(DBG_LED, LOW);
        delay(100);

        if (0 < Serial.available())
        {
            c = Serial.read();
            if (SENTINEL == c)
            {
                // Consume any remaining data and restart
                eatInput();
                break;
            }
        }
    }
}

