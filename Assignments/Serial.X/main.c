 //Title: Serial Interface
// * ---------------------
// * Program Details:
// * This program generates a random number every second up to 100 times and prints it to a serial interface to be able to be monitered
 
// * Inputs: Rx2(rd1)
// * Outputs: Tx2(rd0)
// *
// * Setup: C- Simulator
// * Date: May 5th, 2025
// * File Dependencies / Libraries: 

//#include "C:\Program Files\Microchip\xc8\v3.00\pic\include\proc\pic18f47k42.h"
//#include "C:\Program Files\Microchip\xc8\v2.40\pic\include\proc\pic18f46k42"
//#include "C:\Users\osval\MPLABXProjects\Calculator.X\newxc8_header.h"
//#include "C:\Users\osval\MPLABXProjects\KeypadCalculator.X\newxc8_header.h"
// * Compiler: xc8, 3.0
// * Author: Osvaldo Ramirez
// * Versions:
// *      V1.0: Original Code
// * Useful links:  
// *      Datasheet: https://ww1.microchip.com/downloads/en/DeviceDoc/PIC18(L)F26-27-45-46-47-55-56-57K42-Data-Sheet-40001919G.pdf
// *      PIC18F Instruction Sets: https://onlinelibrary.wiley.com/doi/pdf/10.1002/9781119448457.app4
// *      List of Instrcutions: http://143.110.227.210/faridfarahmand/sonoma/courses/es310/resources/20140217124422790.pdf
// */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcc_generated_files/system/system.h"

/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();
    UART2_Initialize();
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    //INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 


    while(1)
    {
         int num = (rand() % 100) + 1;
        printf("Random: %d\r\n", num);
        __delay_ms(1000); // 1 second delay
    }    
}
