void INTERRUPT_Initialize (void)
{
INTCON0bits.IPEN = 1;    // Enable interrupt priority bit in INTCON0 (check INTCON0 register and find the bit)
INTCON0bits.GIEH = 1;    // Enable high priority interrupts using bits in INTCON0
INTCON0bits.GIEL = 1;   // Enable low priority interrupts using bits in INTCON0
INTCON0bits.INT0EDG = 1;   // Interrupt on rising edge of INT0 pin using bits in INTCON0
IPR1bits.INT0IP = 1;    // Set the interrup high priority (IP) for INT0 - INT0IP
PIE1bits.INT0IE = 1;    // Enable the interrup (IE) for INT0
PIR1bits.INT0IF = 0;
    //Clear interrupt flag for INT0
 
    // Change IVTBASE by doign the following
    // Set IVTBASEU to 0x00
    // Set IVTBASEH to  0x40;
    // Set IVTBASEL to 0x08;
}
void init_ports (void) {

    // Initialization  
    // set port B and D as outputs ANSELD = 0b00000000;
    ANSELD = 0b0000000;
    TRISD = 0b00000000; //sets PORTD as all outputs
    PORTD = 0b00000000; //turns off PORTB outputs so that the LED is initially off
    ANSELB = 0b00000000;
    TRISB = 0b00000111; //sets PORTB.RB0 as input / INT0
    PORTB = 0b00000000;
   // WPUB = 0XFF;//turns off PORTD outputs
}
#define SYS_LED PORTD
#define MOTOR PORTBbits.RB6
#define BUZZER PORTBbits.RB5
#define PR1 PORTBbits.RB1
#define PR2 PORTBbits.RB2
#define EMERGENCY_FLAG PIR1bits.INT0IF
#define ENTER PORTBbits.RB3
#define SECRET_CODE 0x23 