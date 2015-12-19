#ifndef IMAGE_H_
#define IMAGE_H_

#include <TFT.h>
#include <SD.h>

#include "Arduino.h"

#define BUFFER_SIZE 9

class ImageUtil {
  public:
    static void Draw(TFT *screen, char *filename, uint8_t x, uint8_t y);

  private:
    static uint16_t Read2(File f);
    static uint32_t Read4(File f);
};

#endif
