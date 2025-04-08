

/*
 * ---------------------
 * Title: KeyPad Calculator
 * ---------------------
 * Program Details:
 *  This program acts as a calculator which receives two inputs and either adds/subtracts/multiplies/divides them based on the arithmetic operation entered, it also has a clear option that resets the calculator
 * Inputs: PORTB (KeyPad)
 
 *
 * Outputs: PORTD (LEDs)
 *
 * Setup: C- Simulator
 * Date: April 4th, 2025
 * File Dependencies / Libraries: #include <stdio.h> #include <stdlib.h> #include <math.h> #include <xc.h> #include "C:\Program Files\Microchip\xc8\v3.00\pic\include\proc\pic18f47k42.h"
#include "C:\Users\osval\MPLABXProjects\Calculator.X\newxc8_header.h"
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <xc.h>
#include "C:\Program Files\Microchip\xc8\v3.00\pic\include\proc\pic18f47k42.h"
//#include "C:\Program Files\Microchip\xc8\v2.40\pic\include\proc\pic18f46k42"
//#include "C:\Users\osval\MPLABXProjects\Calculator.X\newxc8_header.h"
#include "C:\Users\osval\MPLABXProjects\KeypadCalculator.X\newxc8_header.h"

#define _XTAL_FREQ 4000000 // Fosc frequency for delay library
#define FCY (_XTAL_FREQ / 4)

unsigned int Display_Result_REG = 0;
unsigned int X_Input_REG = 0;
unsigned int Y_Input_REG = 0;
char key = 0;
char key1 = 0;
int digitCount = 0;
int Operation_REG = 0;
char test = 0;


void init_keypad(){
    LATD = 0b00000000;
    ANSELD = 0b00000000;
    TRISD = 0b00000000; // sets PORTD as all outputs
    PORTD = 0b00000000; // turns off PORTD outputs
   
    LATB = 0b00000000;
    ANSELB = 0b00000000;
    PORTB = 0b00000000;
    TRISB = 0b11110000; // sets PORTB as inputs for rows and outputs for columns
}

char get_keypad_input() {
    char key = '\0';

    // Clear all columns
    LATBbits.LATB0 = 0;
    LATBbits.LATB1 = 0;
    LATBbits.LATB2 = 0;
    LATBbits.LATB3 = 0;

    // === Check Column 1 (connected to RB3) ===
    LATBbits.LATB3 = 1;
    if (PORTBbits.RB7) key = '1';
    else if (PORTBbits.RB6) key = '4';
    else if (PORTBbits.RB5) key = '7';
    else if (PORTBbits.RB4) key = '*'; //clear
    LATBbits.LATB3 = 0;

    // === Check Column 2 (connected to RB2) ===
    LATBbits.LATB2 = 1;
    if (PORTBbits.RB7) key = '2';
    else if (PORTBbits.RB6) key = '5';
    else if (PORTBbits.RB5) key = '8';
    else if (PORTBbits.RB4) key = '0';
    LATBbits.LATB2 = 0;

    // === Check Column 3 (connected to RB1) ===
    LATBbits.LATB1 = 1;
    if (PORTBbits.RB7) key = '3';
    else if (PORTBbits.RB6) key = '6';
    else if (PORTBbits.RB5) key = '9';
    else if (PORTBbits.RB4) key = '#'; //equals to
    LATBbits.LATB1 = 0;

    // === Check Column 4 (connected to RB0) ===
    LATBbits.LATB0 = 1;
    if (PORTBbits.RB7) key = 'A'; //addition
    else if (PORTBbits.RB6) key = 'B'; //subtraction
    else if (PORTBbits.RB5) key = 'C'; //multiplication
    else if (PORTBbits.RB4) key = 'D'; //division
    LATBbits.LATB0 = 0;

    // Debounce and wait for release if a key was pressed
    if (key != '\0') {
        __delay_ms(20); // debounce delay
        // Wait for all row inputs to be released
        while (PORTBbits.RB7 || PORTBbits.RB6 || PORTBbits.RB5 || PORTBbits.RB4);
        __delay_ms(20); // debounce release delay//
    }

    return key;
}









unsigned int math(){
        if (Operation_REG == 'A')
        return (X_Input_REG + Y_Input_REG);
        else if (Operation_REG == 'B')
        return (X_Input_REG - Y_Input_REG);
        else if (Operation_REG == 'C')
        return (X_Input_REG * Y_Input_REG);
        else if (Operation_REG == 'D')
        return (X_Input_REG / Y_Input_REG);
}
//Reset all variables and Output
void clear() {
    if (key == '*' || key1 == '*') {
        PORTD = 0;
        digitCount = 0;
        X_Input_REG = 0;
        key = 0;
        key1 = 0;
        Y_Input_REG = 0;
        Operation_REG = 0;
        Display_Result_REG = 0;
       
    }
}

 void main(void) {
     restart: //restart loop
     clear(); //clear command 
    init_keypad();

    while (1) {
        X_Input_REG = 0;
        Y_Input_REG = 0;
        Display_Result_REG = 0;
        digitCount = 0;
        PORTD = 0;

        // --- First number ---
        while (digitCount < 2) {
            key = get_keypad_input();
            if (key >= '0' && key <= '9') {
                X_Input_REG = X_Input_REG * 10 + (key - '0');
                digitCount++;
                __delay_ms(300);  // debounce
            } else if (key == '*') {
                goto restart; // reset if * is pressed
                continue;
            }
        }

        PORTD = 1; // First number entered indication

        // --- Operator ---
        do {
            Operation_REG = get_keypad_input();
            if (Operation_REG == '*')
                goto restart;
        } while (Operation_REG != 'A' && Operation_REG != 'B' && Operation_REG != 'C' && Operation_REG != 'D'); //checks for arithmetic operation

        digitCount = 0;

        // --- Second number ---
        while (digitCount < 2) {
            key1 = get_keypad_input();
            if (key1 >= '0' && key1 <= '9') {
                Y_Input_REG = Y_Input_REG * 10 + (key1 - '0');
                digitCount++;
               __delay_ms(300);  // debounce
            } else if (key1 == '*') {
                goto restart;
                continue;
            }
        }

        PORTD = 2; // Second number entered indication

        // --- Wait for # or * ---
        do {
            test = get_keypad_input();
        } while (test != '#' && test != '*');

        if (test == '#') {
            Display_Result_REG = math(); // do the calculation
            PORTD = Display_Result_REG; //show results on leds
        } else if (test == '*') {
            goto restart;
        }

        __delay_ms(4000); // Short pause before loop restarts
    }
}
