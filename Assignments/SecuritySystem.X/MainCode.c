#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "functions.h"
#include "init.h"


#define SECRET_CODE 0x23  // Can be changed 





void main(void) {
    init_ports();
    INTERRUPT_Initialize();
    
    unsigned char first_input;
    unsigned char second_input;
    unsigned char code_entered;



    while (1) {

        

         first_input = read_input(1);  // PR1

        wait(1500);
        
       
     

         second_input = read_input(2);  // PR2

        wait(1500);

         code_entered = (first_input << 4) | second_input;

        if (code_entered == SECRET_CODE) {
    // Success: short on for a bit then turned off
        MOTOR = 1;
        __delay_ms(4000);
        MOTOR = 0;
        
   
        }else {
    
    play_buzzer_melody();
        }
}
}