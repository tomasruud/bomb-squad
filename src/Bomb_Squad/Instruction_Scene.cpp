#include "Instruction_Scene.h"
#include "Image.h"
#include "Pins.h"

void InstructionScene::Bootstrap() {

  ImageUtil::Draw(_screen, "2/0.bmp", 10, 10);
}

void InstructionScene::HandleFrame(unsigned char frame) {}

SceneID InstructionScene::HandleInput() {

  if(BUTTON_IS_DOWN)
    return SceneID_Game;

  return SceneID_Instructions;
}
