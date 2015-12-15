#ifndef SPLASH_H_
#define SPLASH_H_

#include "Arduino.h"

#define FLAME_MIN_X 99
#define FLAME_MAX_X 104

#define FLAME_MIN_Y 14
#define FLAME_MAX_Y 18

#define PARTICLE_COUNT 3

#define RANDOM_FLAME_X random(FLAME_MIN_X, FLAME_MAX_X)
#define RANDOM_FLAME_Y random(FLAME_MIN_Y, FLAME_MAX_Y)

#endif
