// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <xc.h>
#include "init.h"
#include "config.h"
<<<<<<< HEAD
void wait(unsigned int ms);
unsigned char read_input(unsigned char inputPinBit);
void display_digit(unsigned char digit);
void play_buzzer_melody(void);
void __interrupt(irq(IRQ_INT0), base(0x4008)) INT0_ISR(void);
=======

>>>>>>> 16a26dc850c114406dd9f218296dc05fea644037
// Wait for ms milliseconds
void wait(unsigned int ms) {
    for (unsigned int i = 0; i < ms; i++) {
        __delay_ms(1);
    }
}

// Read PR1 or PR2 depending on parameter
<<<<<<< HEAD
unsigned char read_input(unsigned char inputPinBit) {
    unsigned char count = 0;
    unsigned char prev_state = 0;
    unsigned char curr_state;

    while (count < 4 && PORTBbits.RB3 == 0) { // RB3 = enter button
        curr_state = (PORTB >> inputPinBit) & 1;

        // Detect rising edge
        if (curr_state == 1 && prev_state == 0) {
            count++;
            display_digit(count);
            __delay_ms(300); // debounce
        }

        prev_state = curr_state;
    }    
    __delay_ms(1000);        // Hold it for 1 second
=======
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
>>>>>>> 16a26dc850c114406dd9f218296dc05fea644037

    return count;
}

// Display a binary digit using LEDs on PORTD
void display_digit(unsigned char digit) {
<<<<<<< HEAD
    const char seg_code[] __at(0x200) = {0x3F, 0x06, 0x5B, 0x4F,0x66};
    SYS_LED = seg_code[digit];
=======
    SYS_LED = digit;
>>>>>>> 16a26dc850c114406dd9f218296dc05fea644037
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