/*
 * ---------------------
 * Title: ADC
 * ---------------------
 * Program Details:
 *  This Program uses the concepts of an Analog to Digital Converter, the input was replaced by a photoresistor to measure LUX
 
 * Inputs: RC2(Interrupt) RA0(Voltage divider input for ADC)
 * Outputs: PORTDbits.RD0(LCD), PORTDbits.RD1(LCD), PORTB(LCD) PORTDbits.RD3(LED)
 *
 *
 * Setup: C- Simulator
 * Date: April 29th, 2025
 * File Dependencies / Libraries: #include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "functions.h"
#include "init.h"
#include <string.h>
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
#include <string.h>




/*****************************Main Program*******************************/
#define Vref 3.3 // voltage reference 
int digital; // holds the digital value 
float result;
float voltage; // hold the analog value (volt))
float lux_value;
char data[10];
void main(void)
{       
  INTERRUPT_Initialize();
    LCD_Init();                     /* Initialize 16x2 LCD */
    ADC_Init();
    while (1) {
        ADCON0bits.GO = 1; //Start conversion
        while (ADCON0bits.GO); //Wait for conversion done
        digital = (ADRESH*256) | (ADRESL);/*Combine 8-bit LSB and 2-bit MSB*/
        voltage= digital*((float)Vref/(float)(4096)); 

        if (voltage<1.0){lux_value=voltage*10; }
        if (voltage>1.0){lux_value=voltage*20;}
        if (voltage>1.5){lux_value=voltage*30;}
        if (voltage>1.75){lux_value=voltage*40;}
        if (voltage>2){lux_value=voltage*80;}
        if (voltage>2.5){lux_value=voltage*150;}
        if (voltage>2.75){lux_value=voltage*200;}
        if (voltage>3.0){lux_value=voltage*300;}


    /*It is used to convert integer value to ASCII string*/
    sprintf(data,"%.2f",lux_value);
    strcat(data, " LUX             "); /*Concatenate result and unit to print*/
    LCD_String_xy(1,0,"The Input Light:");
    LCD_String_xy(2,4,data);  //Send the message to the LCD
    MSdelay(100);
          
}
  
}/****************************Functions********************************/
