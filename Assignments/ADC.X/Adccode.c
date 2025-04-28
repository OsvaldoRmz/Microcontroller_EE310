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
             sprintf(data,"%.2f",voltage);
////
     strcat(data," V");	/*Concatenate result and unit to print*/
     LCD_Clear(); 
     LCD_String_xy(2,4,data);/*Send string data for printing*/
     MSdelay(500);   
        // Voltage divider.
       // result =  voltage;
        //converting voltage into LUX Value
        
//        if (voltage<1.0){lux_value=voltage*10; }
//        if (voltage>1.0){lux_value=voltage*20;}
//        if (voltage>1.5){lux_value=voltage*30;}
//        if (voltage>1.75){lux_value=voltage*40;}
//        if (voltage>2){lux_value=voltage*800;}
//        if (voltage>2.5){lux_value=voltage*150;}
//        if (voltage>2.75){lux_value=voltage*200;}
//        if (voltage>3.0){lux_value=voltage*300;}


    /*It is used to convert integer value to ASCII string*/
//    sprintf(data,"%.2f",lux_value);
//    strcat(data, " LUX             "); /*Concatenate result and unit to print*/
//    LCD_String_xy(2,4,data);  //Send the message to the LCD
//    MSdelay(100);
          
}

}/****************************Functions********************************/
