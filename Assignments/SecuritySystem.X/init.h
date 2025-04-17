// init.h
#ifndef INIT_H
#define INIT_H

// --- FUNCTION DECLARATIONS ---
void INTERRUPT_Initialize(void);
void init_ports(void);

// --- HARDWARE DEFINES ---
#define SYS_LED     PORTD
#define MOTOR       PORTBbits.RB6
#define BUZZER      PORTBbits.RB5
#define PR1         PORTBbits.RB1
#define PR2         PORTBbits.RB2
#define ENTER       PORTBbits.RB3
#define EMERGENCY_FLAG PIR1bits.INT0IF

//#define SECRET_CODE 0x23  // You can change this before running

// --- FUNCTION DEFINITIONS ---
void INTERRUPT_Initialize(void) {
    INTCON0bits.IPEN = 1;
    INTCON0bits.GIEH = 1;
    INTCON0bits.GIEL = 1;
    INTCON0bits.INT0EDG = 1;
    IPR1bits.INT0IP = 1;
    PIE1bits.INT0IE = 1;
    PIR1bits.INT0IF = 0;

   
}

void init_ports(void) {
    ANSELD = 0b00000000; // Digital
    TRISD = 0b00000000;  // Output
    PORTD = 0b00000000;

    ANSELB = 0b00000000;
    TRISB = 0b00001111;  // RB0-RB3 inputs, RB5-RB6 outputs
    PORTB = 0b00000000;
}

#endif