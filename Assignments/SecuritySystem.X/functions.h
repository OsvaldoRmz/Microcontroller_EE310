// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <xc.h>
#include "init.h"
#include "config.h"

// Wait for ms milliseconds
void wait(unsigned int ms) {
    for (unsigned int i = 0; i < ms; i++) {
        __delay_ms(1);
    }
}

// Read PR1 or PR2 depending on parameter
unsigned char read_input(unsigned char pr_input) {
    unsigned char count = 0;
    unsigned char last_state = 1;
    unsigned int timeout = 3000;
    unsigned int elapsed = 0;

    while (elapsed < timeout && count < 4) {
        unsigned char current_state = (pr_input == 1) ? PR1 : PR2;

        if (current_state == 0 && last_state == 1) {
            count++;
            wait(300); // Debounce
        }

        last_state = current_state;
        wait(50);
        elapsed += 50;
    }

    return count;
}

// Display a binary digit using LEDs on PORTD
void display_digit(unsigned char digit) {
    SYS_LED = digit;
}

// Emergency melody when interrupt is triggered
void play_buzzer_melody(void) {
    for (int i = 0; i < 5; i++) {
        BUZZER = 1;
        wait(500);
        BUZZER = 0;
        wait(100);
    }
}

// ISR for emergency interrupt
void __interrupt(irq(IRQ_INT0), base(0x4008)) INT0_ISR(void) {
    if (EMERGENCY_FLAG == 1) {
        for (int k = 0; k < 10; k++) {
            BUZZER = 0;
            __delay_ms(250);
            BUZZER = 1;
            __delay_ms(250);
        }
        EMERGENCY_FLAG = 0;
        BUZZER = 0;
    }
}

#endif