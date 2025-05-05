







#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "functions.h"
#include "init.h"
#include <string.h>




/*****************************Main Program*******************************/
 // voltage reference 
 // holds the digital value 

 // hold the analog value (volt))
float lux_value;
char data[10];
void main(void)
{       

    LCD_Init();                     /* Initialize 16x2 LCD */
    ADC_Init();
    while (1) {
        unsigned char difficulty = getDifficulty();
sprintf(data, "Difficulty Level: %d   ", difficulty);  // Create string
LCD_String_xy(1,0, data);  // Display it on line 1, column 0
    if (difficulty == 1) {
   
    } else if (difficulty == 2) {

    } else if (difficulty == 3) {
 
    } else{

        
    }
      

   
          
}
  
}/****************************Functions********************************/