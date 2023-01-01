//
// Horn
//
#include "horn.h"

void horn_warning(void) {
    const int duration = 100U * 1000U;
    ev3_speaker_set_volume(10);

    ev3_speaker_play_tone(NOTE_E4, duration * 2); /* ミ */
    dly_tsk(duration * 2);
    ev3_speaker_stop();
}

void horn_confirmation(void) {
    const int duration = 100U * 1000U;
    ev3_speaker_set_volume(10);

    ev3_speaker_play_tone(NOTE_C4, duration); /* ド */
    dly_tsk(duration);
    ev3_speaker_play_tone(NOTE_F4, duration * 2); /* ファ */
    dly_tsk(duration * 3);
    ev3_speaker_stop();
}
