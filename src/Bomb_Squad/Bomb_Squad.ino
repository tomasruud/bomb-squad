#define USE_DEBUG
#include "Debugger.h"

#include <Thread.h>
#include <ThreadController.h>

#include <SPI.h>
#include <SD.h>
#include <TFT.h>

#include "Colors.h"
#include "Display.h"
#include "Pins.h"
#include "Pitches.h"
#include "Scene.h"
#include "Scenes.h"
#include "Transition.h"

#include "Splash_Scene.h"

#define INPUT_READ_RATE 10

#define DISABLE_AUDIO false
#define MUSIC_BARS 8
#define MUSIC_INTERVAL 1000 / MUSIC_BARS

TFT screen = TFT(TFT_CS, TFT_DC, TFT_RST);

Scene *scenes[] = {
  new SplashScene(&screen)
};

ThreadController thread_pool;
Thread gui_thread;
Thread input_thread;
Thread audio_thread;

Transition transition = Transition(&screen);

SceneID current_scene_id;
Scene *current_scene;
PImage buffer_image;

void setup() {

  DEBUG_START(9600);

  randomSeed(analogRead(5));

  setup_pins();
  setup_screen();
  if(!setup_sd())
    return;

  gui_thread.onRun(gui_render);
  gui_thread.setInterval(FRAME_DURATION);

  input_thread.onRun(read_input);
  input_thread.setInterval(INPUT_READ_RATE);

  audio_thread.onRun(play_audio);
  audio_thread.setInterval(MUSIC_INTERVAL);

  thread_pool.add(&gui_thread);
  thread_pool.add(&input_thread);
  thread_pool.add(&audio_thread);

  current_scene_id = SPLASH_SCREEN;
  load_scene();
}

void loop() {

  thread_pool.run();

  DEBUG(analogRead(KNOB_PIN));
}

void load_scene() {

  current_scene = scenes[current_scene_id];

  char *image = current_scene->Bootstrap();

  if(image != NULL) {
    buffer_image = screen.loadImage(image);
    screen.image(buffer_image, 0, 0);
  }
}

void play_audio() {

  if(DISABLE_AUDIO)
    return;

  static unsigned char bar = 0;

  if(bar == 0) {
    tone(AUDIO_PIN, NOTE_G2, 1000 / 4);
  }

  if(bar >= MUSIC_BARS)
    bar = 0;
  else
    bar++;
}

void read_input() {

  if(current_scene != NULL) {
    SceneID next = current_scene->HandleInput();

    // Change scene only if neccesarry
    if(next != current_scene_id) {
      current_scene_id = next;
      current_scene = NULL;

      transition.ThatsAllFolks();

      load_scene();
    }
  }
}

void gui_render() {

  static unsigned char frame = 0;

  if(current_scene != NULL)
    current_scene->HandleFrame(frame);

  if(frame >= FPS)
    frame = 0;
  else
    frame++;
}


void setup_screen() {

  screen.initR(INITR_BLACKTAB);
  screen.setRotation(1);
  screen.fillScreen(COLOR_BG);
}

bool setup_sd() {

  if(!SD.begin(SD_CS)) {
    screen.println("No SD-card");
    return false;
  }

  return true;
}

void setup_pins() {

  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);

  pinMode(JOY_X_PIN, INPUT);
  pinMode(JOY_Y_PIN, INPUT);
  pinMode(JOY_SW_PIN, INPUT);

  pinMode(AUDIO_PIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT);

  pinMode(KNOB_PIN, INPUT);
}
