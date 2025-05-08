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
/*********************************Delay Function********************************/
void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<165;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
}
unsigned int ADC_Read(void) {
    ADCON0bits.GO = 1;                  // Start conversion
    while (ADCON0bits.GO);             // Wait until complete
    return ((ADRESH << 8) | ADRESL);   // Return 10-bit result
}

unsigned char getDifficulty(void) {
    float voltage;
    unsigned int digital = ADC_Read();
        voltage = digital*((float)Vref/(float)(4096)); 
            if (voltage < 1)
        return 1;    
    else if (voltage > 1)
        return 2;    
    else if (voltage > 1.5)
        return 3;
    else
        return 4;   

}

//        
  #endif