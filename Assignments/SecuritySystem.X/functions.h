#include <xc.h>
#include "functions.h"
#include "init.h"



void display_digit(unsigned char digit) {
    const unsigned char segment_map[] = {
        0x3F, 0x06, 0x5B, 0x4F, // 0-3
        0x66                      // 4
    };
    SEGMENT = segment_map[digit];
}

void play_buzzer_melody(void) {
    for (int i = 0; i < 5; i++) {
        BUZZER = 1;
        wait(100);
        BUZZER = 0;
        wait(100);
    }