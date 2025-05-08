



#pragma config FEXTOSC = LP     // External Oscillator Selection (LP (crystal oscillator) optimized for 32.768 kHz; PFM set to low power)
#pragma config RSTOSC = EXTOSC  // Reset Oscillator Selection (EXTOSC operating per FEXTOSC bits (device manufacturing default))

// CONFIG1H
#pragma config CLKOUTEN = OFF   // Clock out Enable bit (CLKOUT function is disabled)
#pragma config PR1WAY = ON      // PRLOCKED One-Way Set Enable bit (PRLOCK bit can be cleared and set only once)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

// CONFIG2L
#pragma config MCLRE = EXTMCLR  // MCLR Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR )
#pragma config PWRTS = PWRT_OFF // Power-up timer selection bits (PWRT is disabled)
#pragma config MVECEN = ON      // Multi-vector enable bit (Multi-vector enabled, Vector table used for interrupts)
#pragma config IVT1WAY = ON     // IVTLOCK bit One-way set enable bit (IVTLOCK bit can be cleared and set only once)
#pragma config LPBOREN = OFF    // Low Power BOR Enable bit (ULPBOR disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG2H
#pragma config BORV = VBOR_2P45 // Brown-out Reset Voltage Selection bits (Brown-out Reset Voltage (VBOR) set to 2.45V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config DEBUG = OFF      // Debugger Enable bit (Background debugger disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period selection bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled; SWDTEN is ignored)

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4L
#pragma config BBSIZE = BBSIZE_512// Boot Block Size selection bits (Boot Block size is 512 words)
#pragma config BBEN = OFF       // Boot Block enable bit (Boot block disabled)
#pragma config SAFEN = OFF      // Storage Area Flash enable bit (SAF disabled)
#pragma config WRTAPP = OFF     // Application Block write protection bit (Application Block not write protected)

// CONFIG4H
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block not write-protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config WRTSAF = OFF     // SAF Write protection bit (SAF not Write Protected)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)

// CONFIG5L
#pragma config CP = OFF         // PFM and Data EEPROM Code Protection bit (PFM and Data EEPROM code protection disabled)
#define _XTAL_FREQ 4000000                 // Fosc  frequency for _delay()  library
#define FCY    _XTAL_FREQ/4
#include <xc.h>

const char seg_code[8] = {
    0x3F, // 0
    //0x06, // 1
    0x5B, // 2
  //  0x4F, // 3
    0x66, // 4
 //   0x6D, // 5
    0x7D, // 6
   // 0x07, // 7
    0x7F, // 8
 //   0x6F, // 9
    0x77, // A
  //  0x7C, // B
    0x39, // C
 //   0x5E, // D
    0x79, // E
 //   0x71, // F

};

void main() {
    int count = 0;
    LATD = 0b00000000;
    ANSELD = 0b00000000;
    TRISD = 0b00000000; // sets PORTD as all outputs
    PORTD = 0b00000000; // turns off PORTD outputs
   
    LATB = 0b00000000;
    ANSELB = 0b00000000;
    PORTB = 0b00000000;
    TRISB = 0b00000011; // sets PORTB as inputs for rows and outputs for columns

   // RB1 as input (Decrement button)
    PORTD = seg_code[count]; // Display 0 initially

    while(1) {
        if (PORTBbits.RB0 == 1) { // Button pressed (active low)
            __delay_ms(20); // Debounce
            if (PORTBbits.RB0 == 1) {
                count++;
                if (count > 7) 
                    count = 0;
                __delay_ms(1000);
                PORTD = seg_code[count];
                __delay_ms(1000);
                //while(PORTBbits.RB0 == 1); // Wait for release
            }
        }

        if (PORTBbits.RB1 == 1) {
            __delay_ms(20);
            if (PORTBbits.RB1 == 1) {
                count--;
                if (count < 0) 
                    count = 7;
                
                __delay_ms(1000);
                PORTDbits.RD7 = 0;
                PORTD = seg_code[count];
                __delay_ms(1000);
                PORTDbits.RD7 = 1;
                //while(PORTBbits.RB1 == 1);
            }
        }
    }
}



