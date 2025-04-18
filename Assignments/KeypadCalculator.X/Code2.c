

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

unsigned int result = 0;
unsigned int number = 0;
unsigned int number1 = 0;
char key = 0;
char key1 = 0;
int digitCount = 0;
int arithmetic = 0;
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
    else if (PORTBbits.RB4) key = '*';
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
    else if (PORTBbits.RB4) key = '#';
    LATBbits.LATB1 = 0;

    // === Check Column 4 (connected to RB0) ===
    LATBbits.LATB0 = 1;
    if (PORTBbits.RB7) key = 'A';
    else if (PORTBbits.RB6) key = 'B';
    else if (PORTBbits.RB5) key = 'C';
    else if (PORTBbits.RB4) key = 'D';
    LATBbits.LATB0 = 0;

    // Debounce and wait for release if a key was pressed
    if (key != '\0') {
        __delay_ms(20); // debounce delay
        // Wait for all row inputs to be released
        while (PORTBbits.RB7 || PORTBbits.RB6 || PORTBbits.RB5 || PORTBbits.RB4);
        __delay_ms(20); // debounce release delay
    }

    return key;
}









unsigned int math(){
        if (arithmetic == 'A')
        return (number + number1);
        else if (arithmetic == 'B')
        return (number - number1);
        else if (arithmetic == 'C')
        return (number * number1);
        else if (arithmetic == 'D')
        return (number / number1);
}

void clear() {
    if (key == '*' || key1 == '*') {
        PORTD = 0;
        digitCount = 0;
        number = 0;
        key = 0;
        key1 = 0;
        number1 = 0;
        arithmetic = 0;
        result = 0;
    }
}

 void main(void) {
     restart:
     clear();
    init_keypad();

    while (1) {
        number = 0;
        number1 = 0;
        result = 0;
        digitCount = 0;
        PORTD = 0;

        // --- First number ---
        while (digitCount < 2) {
            key = get_keypad_input();
            if (key >= '0' && key <= '9') {
                number = number * 10 + (key - '0');
                digitCount++;
                __delay_ms(300);  // debounce
            } else if (key == '*') {
                clear();
                continue;
            }
        }

        PORTD = 1; // ? First number entered

        // --- Operator ---
        do {
            arithmetic = get_keypad_input();
            if (arithmetic == '*')
                goto restart;
        } while (arithmetic != 'A' && arithmetic != 'B' && arithmetic != 'C' && arithmetic != 'D');

        digitCount = 0;

        // --- Second number ---
        while (digitCount < 2) {
            key1 = get_keypad_input();
            if (key1 >= '0' && key1 <= '9') {
                number1 = number1 * 10 + (key1 - '0');
                digitCount++;
                __delay_ms(300);  // debounce
            } else if (key1 == '*') {
                clear();
                continue;
            }
        }

        PORTD = 2; // ? Second number entered

        // --- Wait for # or * ---
        do {
            test = get_keypad_input();
        } while (test != '#' && test != '*');

        if (test == '#') {
            result = math();
      
           
           
            PORTD = result;
        } else if (test == '*') {
            goto restart;
        }

        __delay_ms(4000); // Short pause before loop restarts
    }
}



