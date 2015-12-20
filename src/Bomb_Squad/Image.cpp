#include "Colors.h"
#include "Display.h"
#include "Image.h"

// Code from Arduino example "SD > spitfbitmap" modified, minified and
// improved commenting based on this:
// http://www.fastgraph.com/help/bmp_header_format.html

uint16_t ImageUtil::Read2(File f) {

  uint16_t result;
  f.read(&result, 2);

  return result;
}

uint32_t ImageUtil::Read4(File f) {

  uint32_t result;
  f.read(&result, 4);

  return result;
}

void ImageUtil::Draw(TFT *screen, uint8_t file_id, uint8_t x, uint8_t y) {

  if((x >= TFT_W) || (y >= TFT_H))
    return;

  char name_buffer[10];
  strcpy_P(name_buffer, (char *) pgm_read_word(&(image_files[file_id])));

  File image_file = SD.open(name_buffer);

  if (image_file == NULL)
    return;

  uint8_t sdbuffer[BUFFER_SIZE];
  uint8_t buffidx = BUFFER_SIZE;

  if(Read2(image_file) == 0x4D42) {

    (void) Read4(image_file); // Skip filesize
    (void) Read4(image_file); // Skip reserved memory

    uint8_t image_offset = Read4(image_file);

    (void) Read4(image_file); // Skip this field

    uint8_t image_width = Read4(image_file);
    uint8_t image_height = Read4(image_file);

    if(Read2(image_file) == 1) { // Planes must be 1

      // Check that image has 24-bit colors and no compression
      if((Read2(image_file) == 24) && (Read4(image_file) == 0)) {
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
