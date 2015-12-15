#ifndef DEBUGGER_H_
#define DEBUGGER_H_

#ifdef USE_DEBUG
#define DEBUG_START(baud) Serial.begin((baud))
#define DEBUG(text) Serial.println(text)
#define DEBUGP(text) Serial.print(text)

#else
#define DEBUG_START
#define DEBUG(text)
#define DEBUGP(text)

#endif

#endif
