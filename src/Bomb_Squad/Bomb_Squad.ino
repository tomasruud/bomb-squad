#define USE_DEBUG false
#include "Debugger.h"

#include "Bomb_Squad.h"
#include "Color.h"

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include <SPI.h>
#include <SD.h>

Adafruit_ST7735 screen = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {

  debug_start();

  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);

  screen.initR(INITR_BLACKTAB);
  screen.setRotation(1);
  screen.fillScreen(RGB(20, 20, 20));

  if(!SD.begin(SD_CS)) {
    screen.println("Could not find SD-card");
    return;
  }
}

void loop() {

}
