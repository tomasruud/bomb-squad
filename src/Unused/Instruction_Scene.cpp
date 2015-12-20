#include "Instruction_Scene.h"
#include "Image.h"
#include "Pins.h"
#include "Display.h"

void InstructionScene::Bootstrap() {

  ImageUtil::Draw(_screen, "2/0.bmp", 10, 10);

  _screen->setCursor(10, 30);
  _screen->setTextSize(FONT_SIZE_SMALL);

  File file = SD.open("0.txt");

  while(file.available()) {
    _screen->print(file.read());
  }

  file.close();
}

void InstructionScene::HandleFrame(unsigned char frame) {}

SceneID InstructionScene::HandleInput() {

  if(BUTTON_IS_DOWN)
    return SceneID_Game;

  return SceneID_Instructions;
}
