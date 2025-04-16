#include <xc.h>
#include "config.h"
#include "functions.h"
#include "init.h"


//#define SECRET_CODE 0x23  // Can be changed 





void main(void) {
    init_ports();
    INTERRUPT_Initialize();


    while (1) {

        

        unsigned char first_input = read_input(1);  // PR1
        display_digit(first_input);
        wait(1500);
        
        loop:
        while (ENTER != 1 ){
            goto loop;
        }
     

        unsigned char second_input = read_input(2);  // PR2
        display_digit(second_input);
        wait(1500);

        unsigned char code_entered = (second_input << 4) | first_input;

        if (code_entered == SECRET_CODE) {
    // Success: short on for a bit then turned off
        MOTOR = 1;
        wait(1000);
        MOTOR = 0;
        wait(1000);
   
        }else {
    
    play_buzzer_melody();
        }
}
}