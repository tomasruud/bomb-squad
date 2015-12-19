#ifndef PINS_H_
#define PINS_H_

#include "Arduino.h"

#define TFT_CS 10
#define TFT_RST 8
#define TFT_DC 9

#define SD_CS 4

// These are flipped because the screen is in portrait
#define X_PIN A2
#define Y_PIN A0

#define AUDIO_PIN A1

#define JOY_Y_PIN A3
#define JOY_X_PIN A4

#define BUTTON_DOWN LOW
#define BUTTON_PIN 5

#define KNOB_PIN A5

#define BLUE_PIN 3
#define ORANGE_PIN 2
#define GREEN_PIN 7
#define YELLOW_PIN 6

#define BUTTON_IS_DOWN (digitalRead(BUTTON_PIN) == BUTTON_DOWN)

#endif
