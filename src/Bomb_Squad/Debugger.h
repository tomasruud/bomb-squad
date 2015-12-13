#ifndef DEBUGGER_H_
#define DEBUGGER_H_

#include "Arduino.h"

#ifndef USE_DEBUG
#define USE_DEBUG true
#endif

// Starts serial only if debugging is on.
void debug_start() {

  if(USE_DEBUG)
    Serial.begin(9600);
}

/**
 * Writes the text to serial only if debugging is on.
 *
 * If debugging is set to false, the compiler will not include the string in the
 * compiled program, meaning you wont waste any space on unused strings. :)
 *
 * Note: If you change the parameter to 'String' instead of 'char *' the
 * compiler will not exclude the strings from your code when compiling.
 *
 * @param text to write
 */
void debug(char *text) {

  if(USE_DEBUG)
    Serial.println(text);
}

#endif
