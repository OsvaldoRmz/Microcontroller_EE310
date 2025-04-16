#include <xc.h>
#include 'config.h'
#include 'functions.h'
#include 'init.h'

#define SECRET_CODE 0x23  // Can be changed 

volatile emergency_flag = 0;

void __interrupt() ISR(void) {
    if (INTF) {
        emergency_flag = 1;
        INTF = 0;
    }
}

void main(void) {
    init_ports();
    init_interrupts();
    init_timer();

    SYS_LED = 1; // System enabled

    while (1) {
        if (emergency_flag) {
            play_buzzer_melody();
            emergency_flag = 0;
            continue;
        }

        unsigned char first_input = read_touchless_input(1);  // PR1
        display_digit(first_input);
        wait(1500);

        unsigned char second_input = read_touchless_input(2);  // PR2
        display_digit(second_input);
        wait(1500);

        unsigned char code_entered = (second_input << 4) | first_input;

        if (code_entered == SECRET_CODE) {
    // Success: short success beeps
            for (int i = 0; i < 3; i++) {
        BUZZER = 1;
        wait(100);
        BUZZER = 0;
        wait(100);
    }
        }else {
    // Error: buzzer stays on
    BUZZER = 1;
    wait(2000);
    BUZZER = 0;
}
}
}