
/*
 * ---------------------
 * Title: Security System
 * ---------------------
 * Program Details:
 *  A secret code is built into this program. This Program takes an input via photo resistors and if the input is equal to the secret code it turns on a motor, if it doesn't a buzzer sends out a melody
 
 * Inputs: ENTER(RB3), INTERRUPT(RB0), PHOTORESISISTOR(PR1)(RB1), PHOTORESISISTOR(PR2)(RB2)
 * Outputs: PORTD (LEDs), MOTOR(RB6), BUZZER(RB5)
 *
 *
 * Setup: C- Simulator
 * Date: April 18th, 2025
 * File Dependencies / Libraries: #include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <xc.h>
#include "C:\Program Files\Microchip\xc8\v3.00\pic\include\proc\pic18f47k42.h"
//#include "C:\Program Files\Microchip\xc8\v2.40\pic\include\proc\pic18f46k42"
//#include "C:\Users\osval\MPLABXProjects\Calculator.X\newxc8_header.h"
#include "C:\Users\osval\MPLABXProjects\KeypadCalculator.X\newxc8_header.h"
 * Compiler: xc8, 3.0
 * Author: Osvaldo Ramirez
 * Versions:
 *      V1.0: Original Code
 * Useful links:  
 *      Datasheet: https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18(L)F26-27-45-46-47-55-56-57K42-Data-Sheet-40001919G.pdf
 *      PIC18F Instruction Sets: https://onlinelibrary.wiley.com/doi/pdf/10.1002/9781119448457.app4
 *      List of Instrcutions: http://143.110.227.210/faridfarahmand/sonoma/courses/es310/resources/20140217124422790.pdf
 */





#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "functions.h"
#include "init.h"


//#define SECRET_CODE 0x23  // Can be changed 





void main(void) {
    init_ports();
    INTERRUPT_Initialize();
    
    unsigned char first_input;
    unsigned char second_input;
    unsigned char code_entered;



    while (1) {

        

         first_input = read_input(1);  // PR1
        display_digit(first_input);
        wait(1500);
        
       
        while (ENTER != 1)
       
     

         second_input = read_input(2);  // PR2
        display_digit(second_input);
        wait(1500);

         code_entered = (second_input << 4) | first_input;

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
