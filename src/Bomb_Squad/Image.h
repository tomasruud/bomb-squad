#ifndef IMAGE_H_
#define IMAGE_H_

#include <TFT.h>
#include <SD.h>

#include <avr/pgmspace.h>

#include "Arduino.h"

#define BUFFER_SIZE 9

const char image_big_logo[] PROGMEM = "0/0.bmp";
const char image_copyright[] PROGMEM = "0/1.bmp";

const char image_difficulty[] PROGMEM = "1/0.bmp";
const char image_diff_easy[] PROGMEM = "1/1.bmp";
const char image_diff_med[] PROGMEM = "1/2.bmp";
const char image_diff_hard[] PROGMEM = "1/3.bmp";
const char image_bomb[] PROGMEM = "1/4.bmp";

const char image_game_over[] PROGMEM = "3/0.bmp";
const char image_explode[] PROGMEM = "3/1.bmp";
const char image_nice[] PROGMEM = "3/2.bmp";

const char image_quest[] PROGMEM = "4/0.bmp";
const char image_updown[] PROGMEM = "4/1.bmp";

const char image_timer[] PROGMEM = "0.bmp";

const char * const image_files[] PROGMEM = {
  image_big_logo,
  image_copyright,
  image_difficulty,
  image_diff_easy,
  image_diff_med,
  image_diff_hard,
  image_bomb,
  image_game_over,
  image_explode,
  image_nice,
  image_quest,
  image_updown,
  image_timer
};

class ImageUtil {
  public:
    static void Draw(TFT *screen, uint8_t file_id, uint8_t x, uint8_t y);

  private:
    static uint16_t Read2(File f);
    static uint32_t Read4(File f);
};

#endif
