#ifndef AUDIO_H_
#define AUDIO_H_

#define MUSIC_BARS 8
#define MUSIC_INTERVAL 1000 / MUSIC_BARS

void play_audio() {

  static unsigned char bar = 0;

  if(bar == 0)
    tone(AUDIO_PIN, NOTE_G2, 1000 / 4);

  if(bar >= MUSIC_BARS)
    bar = 0;
  else
    bar++;
}

#endif
