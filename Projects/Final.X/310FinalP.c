#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "functions.h"
#include "init.h"
#include <string.h>
//#include <time.h>



/*****************************Main Program*******************************/
 // voltage reference 
 // holds the digital value 

 // hold the analog value (volt))
#define Vref 3.3 
float voltage;
int digital;
float Difficulty;
char data[10];
float count1;
int count2;
int num;


void main(void)
{       
Back:

    LCD_Init();                     /* Initialize 16x2 LCD */
    ADC_Init();
    count2 = 0;
    count1 = 0;
    
    //srand(time(NULL));
    
    while (1) {
       ADCON0bits.GO = 1; //Start conversion
        while (ADCON0bits.GO); //Wait for conversion done
        digital = (ADRESH*256) | (ADRESL);/*Combine 8-bit LSB and 2-bit MSB*/
        voltage= digital*((float)Vref/(float)(4096)); 
        if (voltage<1.0){Difficulty = 1;}
        if (voltage>1.0){Difficulty = 2;}
        if (voltage>1.5){Difficulty = 3;}
        
        if (voltage>2){Difficulty = 4;}
      
      


    /*It is used to convert integer value to ASCII string*/
        sprintf(data,"%.2f",Difficulty);
  /*Concatenate result and unit to print*/
        LCD_String_xy(1,0,"Difficulty Level:");
        LCD_String_xy(2,4,data);  //Send the message to the LCD

        MSdelay(100);
    if (BUTTON1 == 0){
        LCD_Clear();
        LCD_String_xy(1,0,"Starting in 3:");
        __delay_ms(1000);
        LCD_String_xy(1,0,"Starting in 2:");
        __delay_ms(1000);
        LCD_String_xy(1,0,"Starting in 1:");
        __delay_ms(1000);
        LCD_Clear();
        while(1){
                 if (Difficulty == 4){
                 num = (rand() % 16); 
                PORTD = num;
                __delay_ms(250);
                PORTD = 0;
                __delay_ms(100);
                LCD_String_xy(1,0,"Enter Guess:");
                LCD_String_xy(2,4,"0.00");  //Send the message to the LCD
                while (PORTDbits.RD6 == 1){
                    if (PORTEbits.RE1 == 0){
                        count1 ++;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                    }
                    if (PORTEbits.RE0 == 0){
                        count1 --;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                       
                    }
                    
                        
                      
                }
                if (num == count1){
                        LCD_Clear();
                        count2 = count2 + 1;
                        LCD_String_xy(1,0,"YOU WIN!!");
                        __delay_ms(5000);
                        count1 = 0;
                        
                     
                    }
                else {
                     LCD_Clear();
                     LCD_String_xy(1,0,"YOU LOSE :( ");
                     __delay_ms(5000);
                     count1 = 0;
                     
                     
                        
                    }
                LCD_Clear();
                LCD_String_xy(1,0,"Next Stage in 3:");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 2");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 1:");
                __delay_ms(1000);
                LCD_Clear();
                num = (rand() % 16); 
                PORTD = num;
                __delay_ms(150);
                PORTD = 0;
                __delay_ms(100);
                LCD_String_xy(1,0,"Enter Guess:");
                LCD_String_xy(2,4,"0.00");  //Send the message to the LCD
                while (PORTDbits.RD6 == 1){
                    if (PORTEbits.RE1 == 0){
                        count1 ++;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                    }
                    if (PORTEbits.RE0 == 0){
                        count1 --;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                       
                    }
                }
                if (num == count1){
                        LCD_Clear();
                        count2 = count2 + 1;
                        LCD_String_xy(1,0,"YOU WIN!!");
                        __delay_ms(5000);
                        count1 = 0;
                        
                     
                    }
                else {
                     LCD_Clear();
                     LCD_String_xy(1,0,"YOU LOSE :( ");
                     __delay_ms(5000);
                     count1 = 0;
                }
                    LCD_Clear();
                LCD_String_xy(1,0,"Next Stage in 3:");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 2");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 1:");
                __delay_ms(1000);
                LCD_Clear();
                num = (rand() % 16); 
                PORTD = num;
                __delay_ms(50);
                PORTD = 0;
                __delay_ms(100);
                LCD_String_xy(1,0,"Enter Guess:");
                LCD_String_xy(2,4,"0.00");  //Send the message to the LCD
                while (PORTDbits.RD6 == 1){
                    if (PORTEbits.RE1 == 0){
                        count1 ++;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                    }
                    if (PORTEbits.RE0 == 0){
                        count1 --;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                       
                    }
                    
                }     
                    if (num == count1){
                        LCD_Clear();
                        count2 = count2 + 1;
                        LCD_String_xy(1,0,"YOU WIN!!");
                        __delay_ms(5000);
                        count1 = 0;
                        
                     
                    }
                else {
                     LCD_Clear();
                     LCD_String_xy(1,0,"YOU LOSE :( ");
                     __delay_ms(5000);
                     count1 = 0;
                     
                     
                        
                    }
                if (count2 == 0) {
                    LCD_String_xy(1,0,"Final Score:");
                    LCD_String_xy(2,4,"0/3");  //Send the message to the LCD
                    __delay_ms(5000);
                    goto Back;  
                }
                sprintf(data,"%1.0d",count2);
                LCD_String_xy(1,0,"Final Score:");
                strcat(data,"/3");
                LCD_String_xy(2,4,data);  //Send the message to the LCD
                __delay_ms(5000);
                goto Back;  
                }
/////////////////////////////DIFF 3//////////////////////////////////////////////
                 if (Difficulty == 3){
                 num = (rand() % 16); 
                PORTD = num;
                __delay_ms(1000);
                PORTD = 0;
                __delay_ms(100);
                LCD_String_xy(1,0,"Enter Guess:");
                LCD_String_xy(2,4,"0.00");  //Send the message to the LCD
                while (PORTDbits.RD6 == 1){
                    if (PORTEbits.RE1 == 0){
                        count1 ++;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                    }
                    if (PORTEbits.RE0 == 0){
                        count1 --;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                       
                    }
                    
                        
                      
                }
                if (num == count1){
                        LCD_Clear();
                        count2 = count2 + 1;
                        LCD_String_xy(1,0,"YOU WIN!!");
                        __delay_ms(5000);
                        count1 = 0;
                        
                     
                    }
                else {
                     LCD_Clear();
                     LCD_String_xy(1,0,"YOU LOSE :( ");
                     __delay_ms(5000);
                     count1 = 0;
                     
                     
                        
                    }
                LCD_Clear();
                LCD_String_xy(1,0,"Next Stage in 3:");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 2");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 1:");
                __delay_ms(1000);
                LCD_Clear();
                num = (rand() % 16); 
                PORTD = num;
                __delay_ms(500);
                PORTD = 0;
                __delay_ms(100);
                LCD_String_xy(1,0,"Enter Guess:");
                LCD_String_xy(2,4,"0.00");  //Send the message to the LCD
                while (PORTDbits.RD6 == 1){
                    if (PORTEbits.RE1 == 0){
                        count1 ++;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                    }
                    if (PORTEbits.RE0 == 0){
                        count1 --;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                       
                    }
                }
                if (num == count1){
                        LCD_Clear();
                        count2 = count2 + 1;
                        LCD_String_xy(1,0,"YOU WIN!!");
                        __delay_ms(5000);
                        count1 = 0;
                        
                     
                    }
                else {
                     LCD_Clear();
                     LCD_String_xy(1,0,"YOU LOSE :( ");
                     __delay_ms(5000);
                     count1 = 0;
                }
                    LCD_Clear();
                LCD_String_xy(1,0,"Next Stage in 3:");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 2");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 1:");
                __delay_ms(1000);
                LCD_Clear();
                num = (rand() % 16); 
                PORTD = num;
                __delay_ms(250);
                PORTD = 0;
                __delay_ms(100);
                LCD_String_xy(1,0,"Enter Guess:");
                LCD_String_xy(2,4,"0.00");  //Send the message to the LCD
                while (PORTDbits.RD6 == 1){
                    if (PORTEbits.RE1 == 0){
                        count1 ++;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                    }
                    if (PORTEbits.RE0 == 0){
                        count1 --;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                       
                    }
                    
                }     
                    if (num == count1){
                        LCD_Clear();
                        count2 = count2 + 1;
                        LCD_String_xy(1,0,"YOU WIN!!");
                        __delay_ms(5000);
                        count1 = 0;
                        
                     
                    }
                else {
                     LCD_Clear();
                     LCD_String_xy(1,0,"YOU LOSE :( ");
                     __delay_ms(5000);
                     count1 = 0;
                     
                     
                        
                    }
                if (count2 == 0) {
                    LCD_String_xy(1,0,"Final Score:");
                    LCD_String_xy(2,4,"0/3");  //Send the message to the LCD
                    __delay_ms(5000);
                    goto Back;  
                }
                sprintf(data,"%1.0d",count2);
                LCD_String_xy(1,0,"Final Score:");
                strcat(data,"/3");
                LCD_String_xy(2,4,data);  //Send the message to the LCD
                __delay_ms(5000);
                goto Back;  
                }
///////////////////////////////////DIFF 2//////////////////////////////////////
                 if (Difficulty == 2){
                 num = (rand() % 16); 
                PORTD = num;
                __delay_ms(1500);
                PORTD = 0;
                __delay_ms(100);
                LCD_String_xy(1,0,"Enter Guess:");
                LCD_String_xy(2,4,"0.00");  //Send the message to the LCD
                while (PORTDbits.RD6 == 1){
                    if (PORTEbits.RE1 == 0){
                        count1 ++;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                    }
                    if (PORTEbits.RE0 == 0){
                        count1 --;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                       
                    }
                    
                        
                      
                }
                if (num == count1){
                        LCD_Clear();
                        count2 = count2 + 1;
                        LCD_String_xy(1,0,"YOU WIN!!");
                        __delay_ms(5000);
                        count1 = 0;
                        
                     
                    }
                else {
                     LCD_Clear();
                     LCD_String_xy(1,0,"YOU LOSE :( ");
                     __delay_ms(5000);
                     count1 = 0;
                     
                     
                        
                    }
                LCD_Clear();
                LCD_String_xy(1,0,"Next Stage in 3:");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 2");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 1:");
                __delay_ms(1000);
                LCD_Clear();
                num = (rand() % 16); 
                PORTD = num;
                __delay_ms(1250);
                PORTD = 0;
                __delay_ms(100);
                LCD_String_xy(1,0,"Enter Guess:");
                LCD_String_xy(2,4,"0.00");  //Send the message to the LCD
                while (PORTDbits.RD6 == 1){
                    if (PORTEbits.RE1 == 0){
                        count1 ++;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                    }
                    if (PORTEbits.RE0 == 0){
                        count1 --;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                       
                    }
                }
                if (num == count1){
                        LCD_Clear();
                        count2 = count2 + 1;
                        LCD_String_xy(1,0,"YOU WIN!!");
                        __delay_ms(5000);
                        count1 = 0;
                        
                     
                    }
                else {
                     LCD_Clear();
                     LCD_String_xy(1,0,"YOU LOSE :( ");
                     __delay_ms(5000);
                     count1 = 0;
                }
                    LCD_Clear();
                LCD_String_xy(1,0,"Next Stage in 3:");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 2");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 1:");
                __delay_ms(1000);
                LCD_Clear();
                num = (rand() % 16); 
                PORTD = num;
                __delay_ms(1000);
                PORTD = 0;
                __delay_ms(100);
                LCD_String_xy(1,0,"Enter Guess:");
                LCD_String_xy(2,4,"0.00");  //Send the message to the LCD
                while (PORTDbits.RD6 == 1){
                    if (PORTEbits.RE1 == 0){
                        count1 ++;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                    }
                    if (PORTEbits.RE0 == 0){
                        count1 --;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                       
                    }
                    
                }     
                    if (num == count1){
                        LCD_Clear();
                        count2 = count2 + 1;
                        LCD_String_xy(1,0,"YOU WIN!!");
                        __delay_ms(5000);
                        count1 = 0;
                        
                     
                    }
                else {
                     LCD_Clear();
                     LCD_String_xy(1,0,"YOU LOSE :( ");
                     __delay_ms(5000);
                     count1 = 0;
                     
                     
                        
                    }
                if (count2 == 0) {
                    LCD_String_xy(1,0,"Final Score:");
                    LCD_String_xy(2,4,"0/3");  //Send the message to the LCD
                    __delay_ms(5000);
                    goto Back;  
                }
                sprintf(data,"%1.0d",count2);
                LCD_String_xy(1,0,"Final Score:");
                strcat(data,"/3");
                LCD_String_xy(2,4,data);  //Send the message to the LCD
                __delay_ms(5000);
                goto Back;  
                }
//////////////////////////////////DIFF 1////////////////////////////////////////
                 if (Difficulty == 1){
                 num = (rand() % 16); 
                PORTD = num;
                __delay_ms(2000);
                PORTD = 0;
                __delay_ms(100);
                LCD_String_xy(1,0,"Enter Guess:");
                LCD_String_xy(2,4,"0.00");  //Send the message to the LCD
                while (PORTDbits.RD6 == 1){
                    if (PORTEbits.RE1 == 0){
                        count1 ++;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                    }
                    if (PORTEbits.RE0 == 0){
                        count1 --;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                       
                    }
                    
                        
                      
                }
                if (num == count1){
                        LCD_Clear();
                        count2 = count2 + 1;
                        LCD_String_xy(1,0,"YOU WIN!!");
                        __delay_ms(5000);
                        count1 = 0;
                        
                     
                    }
                else {
                     LCD_Clear();
                     LCD_String_xy(1,0,"YOU LOSE :( ");
                     __delay_ms(5000);
                     count1 = 0;
                     
                     
                        
                    }
                LCD_Clear();
                LCD_String_xy(1,0,"Next Stage in 3:");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 2");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 1:");
                __delay_ms(1000);
                LCD_Clear();
                num = (rand() % 16); 
                PORTD = num;
                __delay_ms(1750);
                PORTD = 0;
                __delay_ms(100);
                LCD_String_xy(1,0,"Enter Guess:");
                LCD_String_xy(2,4,"0.00");  //Send the message to the LCD
                while (PORTDbits.RD6 == 1){
                    if (PORTEbits.RE1 == 0){
                        count1 ++;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                    }
                    if (PORTEbits.RE0 == 0){
                        count1 --;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                       
                    }
                }
                if (num == count1){
                        LCD_Clear();
                        count2 = count2 + 1;
                        LCD_String_xy(1,0,"YOU WIN!!");
                        __delay_ms(5000);
                        count1 = 0;

                    }
                else {
                     LCD_Clear();
                     LCD_String_xy(1,0,"YOU LOSE :( ");
                     __delay_ms(5000);
                     count1 = 0;
                }
                    LCD_Clear();
                LCD_String_xy(1,0,"Next Stage in 3:");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 2");
                __delay_ms(1000);
                LCD_String_xy(1,0,"Next Stage in 1:");
                __delay_ms(1000);
                LCD_Clear();
                num = (rand() % 16); 
                PORTD = num;
                __delay_ms(1500);
                PORTD = 0;
                __delay_ms(100);
                LCD_String_xy(1,0,"Enter Guess:");
                LCD_String_xy(2,4,"0.00");  //Send the message to the LCD
                while (PORTDbits.RD6 == 1){
                    if (PORTEbits.RE1 == 0){
                        count1 ++;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                    }
                    if (PORTEbits.RE0 == 0){
                        count1 --;
                        __delay_ms(250);
                         sprintf(data,"%.2f",count1);
                       LCD_String_xy(1,0,"Enter Guess:");
                       LCD_String_xy(2,4,data);  //Send the message to the LCD
                       
                    }
                    
                }     
                    if (num == count1){
                        LCD_Clear();
                        count2 = count2 + 1;
                        LCD_String_xy(1,0,"YOU WIN!!");
                        __delay_ms(5000);
                        count1 = 0;
 
                    }
                else {
                     LCD_Clear();
                     LCD_String_xy(1,0,"YOU LOSE :( ");
                     __delay_ms(5000);
                     count1 = 0;
                     
    
                    }
                if (count2 == 0) {
                    LCD_String_xy(1,0,"Final Score:");
                    LCD_String_xy(2,4,"0/3");  //Send the message to the LCD
                    __delay_ms(5000);
                    goto Back;  
                }
                sprintf(data,"%1.0d",count2);
                LCD_String_xy(1,0,"Final Score:");
                strcat(data,"/3");
                LCD_String_xy(2,4,data);  //Send the message to the LCD
                __delay_ms(5000);
                goto Back;  
                }
        }
    }
    }
}

    

    

    
      

   
          

