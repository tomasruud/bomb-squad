#include "Instruction_Scene.h"
#include "Image.h"
#include "Button.h"

void InstructionScene::Bootstrap() {

  _flags.has_drawn = 0x0;

  draw_image(_screen, "instruct/header.bmp", 10, 10);
}

void InstructionScene::HandleFrame(unsigned char frame) {

  if(!_flags.has_drawn) {
    _flags.has_drawn = 0x1;

  }
}

SceneID InstructionScene::HandleInput() {

  if(BUTTON_IS_DOWN)
    return SceneID_Game;

  return SceneID_Instructions;
}
