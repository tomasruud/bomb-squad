#include "Instruction_Scene.h"
#include "Image.h"

void InstructionScene::Bootstrap() {

  _flags.has_drawn = 0x0;

  draw_image(_screen, HEADER_FILE, 10, 10);
}

void InstructionScene::HandleFrame(unsigned char frame) {

  if(!_flags.has_drawn) {
    _flags.has_drawn = 0x1;

  }
}

SceneID InstructionScene::HandleInput() {

  return SceneID_Instructions;
}
