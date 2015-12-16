#ifndef IMAGE_H_
#define IMAGE_H_

#include <TFT.h>

#include "Arduino.h"

#define BUFFPIXEL 1

void draw_image(TFT *screen, char *filename, uint8_t x, uint8_t y);

#endif
