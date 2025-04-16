#include <xc.h>
#include "config.h"
#include "init.h"




void wait(unsigned int ms) {
    for (unsigned int i = 0; i < ms; i++) {
        __delay_ms(1);
    }
}

unsigned char read_input(unsigned char pr_input) {
    unsigned char count = 0;
    unsigned char last_state = 1;
    unsigned int timeout = 3000;

    unsigned int elapsed = 0;
    while (elapsed < timeout && count < 4) {
        unsigned char current_state = (pr_input == 1) ? PR1 : PR2;

        if (current_state == 0 && last_state == 1) {
            count++;
            wait(300); // debounce
        }

        last_state = current_state;
        wait(50);
        elapsed += 50;
    }

    return count;
}

void display_digit(unsigned char digit) {
    SYS_LED = digit;
}
void play_buzzer_melody(void) {
    for (int i = 0; i < 5; i++) {
        BUZZER = 1;
        wait(500);
        BUZZER = 0;
        wait(100);
    }
}
void __interrupt(irq(IRQ_INT0),base(0x4008)) INT0_ISR(void)
{
       if(EMERGENCY_FLAG == 1) // Check if interrupt flag for INT0 is set to 1 - (note INT0 is your input)
           for (int k = 0; k<10;k++){
        BUZZER = 0;//turns on LED
        __delay_ms(250);//delays for 1 second
        //PORTD=0b00000011;//turns off LED
         BUZZER = 1;//turns on LED    
        __delay_ms(250);//delays for 1 second
        }
           
            // if so, do something
       EMERGENCY_FLAG = 0;
       BUZZER = 0;
    }