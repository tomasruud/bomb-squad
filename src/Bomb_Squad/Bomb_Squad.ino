#define USE_DEBUG
#include "Debugger.h"

#include <Thread.h>
#include <ThreadController.h>

#include <SPI.h>
#include <SD.h>
#include <TFT.h>

#include "Colors.h"
#include "Display.h"
#include "Globals.h"
#include "Image.h"
#include "Pins.h"
#include "Pitches.h"
#include "Scene.h"
#include "Scene_Factory.h"
#include "Scene_ID.h"
#include "Transition.h"

#define INPUT_READ_RATE 10
#define BOOT_SCENE SceneID_Splash

TFT screen = TFT(TFT_CS, TFT_DC, TFT_RST);

ThreadController thread_pool;
Thread gui_thread;
Thread input_thread;

Transition transition = Transition(&screen);

SceneID current_scene_id;
Scene *current_scene;

unsigned char g_level = 0;
unsigned char g_difficulty = 0;

void setup() {

  DEBUG_START(9600);

  randomSeed(analogRead(5));

  setup_pins();
  setup_screen();
  if(!setup_sd())
    return;

  gui_thread.onRun(gui_render);
  gui_thread.setInterval(FRAME_DURATION);

  input_thread.onRun(handle_input);
  input_thread.setInterval(INPUT_READ_RATE);

  thread_pool.add(&gui_thread);
  thread_pool.add(&input_thread);

  current_scene_id = BOOT_SCENE;
  load_scene();
}

void loop() {

  thread_pool.run();
}

void load_scene() {

  DEBUGP("Difficulty: ");
  DEBUG(g_difficulty);

  current_scene = SceneFactory::Create(current_scene_id, &screen);

  if(current_scene == NULL) {
    screen.setTextColor(COLOR_TEXT);
    screen.setCursor(4, 4);
    screen.println("No scene");
    return;
  }

  current_scene->Bootstrap();
}

void handle_input() {

  if(current_scene != NULL) {
    SceneID next = current_scene->HandleInput();

    // Change scene only if neccesarry
    if(next != NULL && next != current_scene_id) {
      delete current_scene;
      current_scene = NULL;

      current_scene_id = next;

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
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(AUDIO_PIN, OUTPUT);

  pinMode(KNOB_PIN, INPUT);
}
