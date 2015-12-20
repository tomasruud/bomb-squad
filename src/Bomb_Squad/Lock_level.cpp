#include "Lock_Level.h"

#include "Pins.h"

void LockLevel::Bootstrap() {
}

void LockLevel::HandleFrame(unsigned char frame) {


}

LevelAction LockLevel::HandleLevelInput() {

  if(BUTTON_IS_DOWN)
    return NEXT;

  return STAY;
}
