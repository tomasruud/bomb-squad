#include "Colors.h"
#include "Display.h"
#include "Image.h"

#include <SD.h>

// Code from Arduino example SD > spitfbitmap modified and minified and
// improved commenting based on this:
// http://www.fastgraph.com/help/bmp_header_format.html

static uint16_t read2(File f) {

  uint16_t result;

  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();

  return result;
}

static uint32_t read4(File f) {

  uint32_t result;

  ((uint8_t *)&result)[0] = f.read();
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read();

  return result;
}

void draw_image(TFT *screen, char *filename, uint8_t x, uint8_t y) {

  if((x >= TFT_W) || (y >= TFT_H))
    return;

  File image_file = SD.open(filename);

  if (image_file == NULL)
    return;

  uint8_t sdbuffer[BUFFER_SIZE];
  uint8_t buffidx = BUFFER_SIZE;

  if(read2(image_file) == 0x4D42) {

    (void) read4(image_file); // Skip filesize
    (void) read4(image_file); // Skip reserved memory

    uint8_t image_offset = read4(image_file);

    (void) read4(image_file); // Skip this field

    uint8_t image_width = read4(image_file);
    uint8_t image_height = read4(image_file);

    if(read2(image_file) == 1) { // Planes must be 1

      // Check that image has 24-bit colors and no compression
      if((read2(image_file) == 24) && (read4(image_file) == 0)) {
        uint16_t image_row_size = (image_width * 3 + 3) & ~3;

        uint8_t w = image_width;
        uint8_t h = image_height;

        if((x + w - 1) >= TFT_W)
          w = TFT_W - x;

        if((y + h - 1) >= TFT_H)
          h = TFT_H - y;

        screen->setAddrWindow(x, y, x + w - 1, y + h - 1);

        for (uint8_t row = 0; row < h; row++) {
          uint32_t pos = image_offset + (image_height - 1 - row) * image_row_size;

          if(image_file.position() != pos) {
            image_file.seek(pos);
            buffidx = BUFFER_SIZE;
          }

          for (uint8_t col = 0; col < w; col++) {
            if (buffidx >= BUFFER_SIZE) {
              image_file.read(sdbuffer, BUFFER_SIZE);
              buffidx = 0;
            }

            uint8_t b = sdbuffer[buffidx++];
            uint8_t g = sdbuffer[buffidx++];
            uint8_t r = sdbuffer[buffidx++];

            screen->pushColor(RGB(r, g, b));
          }
        }
      }
    }
  }

  image_file.close();
}
