#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <xc.h>
#include "init.h"
#include "config.h"
  

void MSdelay(unsigned int );
void LCD_Command(char );
void LCD_Char(char x);
void LCD_String(const char *);
void LCD_String_xy(char ,char ,const char*);
void LCD_Clear();
//void Timer1_Init(void);
//void Timer1_Start(void);
//void Timer1_Stop(void);
//uint16_t Timer1_Read(void);

void LCD_Clear()
{
        LCD_Command(0x01); /* clear display screen */
}

void LCD_Command(char cmd )
{
    ldata= cmd;            /* Send data to PORT as a command for LCD */   
    RS = 0;                /* Command Register is selected */
    EN = 1;                /* High-to-Low pulse on Enable pin to latch data */ 
    NOP();
    EN = 0;
    MSdelay(3); 
}

void LCD_Char(char dat)
{
    ldata= dat;            /* Send data to LCD */  
    RS = 1;                /* Data Register is selected */
    EN=1;                  /* High-to-Low pulse on Enable pin to latch data */   
    NOP();
    EN=0;
    MSdelay(1);
}


void LCD_String(const char *msg)
{
    while((*msg)!=0)
    {       
      LCD_Char(*msg);
      msg++;    
        }
}

void LCD_String_xy(char row,char pos,const char *msg)
{
    char location=0;
    if(row<=1)
    {
        location=(0x80) | ((pos) & 0x0f); /*Print message on 1st row and desired location*/
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f); /*Print message on 2nd row and desired location*/
        LCD_Command(location);    
    }  
    LCD_String(msg);

}

void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<165;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
}
//void Timer1_Init(void) {
//    T1CON = 0x00;          // Clear
//    T1CLK = 0x01;          // Fosc/4
//    T1GCON = 0x00;         // Disable gate
//    T1CONbits.T1RD16 = 1;  // Enable 16-bit read
//    TMR1H = 0;             // Reset timer
//    TMR1L = 0;
//    T1CONbits.TMR1ON = 1;  // Turn it on
////    T1CON = 0x30;   // TMR1 ON, Fosc/4, prescaler 1:8
////    TMR1H = 0;
////    TMR1L = 0;
////    T1CONbits.T1RD16 = 1;
//}
//
//void Timer1_Start(void) {
//    TMR1H = 0;
//    TMR1L = 0;
//    T1CONbits.TMR1ON = 1;
//}
//
//void Timer1_Stop(void) {
//    T1CONbits.TMR1ON = 0;
//}
//
//uint16_t Timer1_Read(void) {
//    return ((uint16_t)TMR1H << 8) | TMR1L;
//}

  #endif