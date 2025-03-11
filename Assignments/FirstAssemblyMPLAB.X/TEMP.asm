;---------------------
; Title: Heating and Cooling Control System
;---------------------
; Program Details:
; The purpose of this program is to determine whether a cooling/heating system 
    ;needs to be turned on or off or do nothing at all

; Inputs: Inner_loop ,Outer_loop 
; Outputs: PORTD
; Date: March 7, 2025
; File Dependencies / Libraries: #include ".\AssemblyConfig.inc"
; Compiler: xc8, 2.46
; Author: Osvaldo Ramirez
; Versions:
;       V1.0 3/7/25 - First Version



;---------------------
; Initialization 
;---------------------
#include ".\AssemblyConfig.inc"
;#include "C:\Users\student\Documents\myMPLABXProjects\ProjectFirstAssemblyMPLAB\FirstAssemblyMPLAB.X\AssemblyConfig.inc"

#include <xc.inc>
PSECT absdata,abs,ovrld ;do not change
;---------------------
; Program Inputs
;---------------------
#define measuredTempInput -5 ;input measuered value in decimal
#define refTempInput 15 ;input refereence value in decimal
 
;---------------------
; Program Constants
;---------------------
refTemp	EQU 20h  
measuredTemp EQU 21h
contReg	EQU 22h
MUnits EQU 70h
MTens EQU  71h
MHundred EQU 72h
RUnits EQU 60h
RTens EQU 61h
RHundred EQU 62h
COUNTER EQU 23h
COUNTER2 EQU 24h
;---------------------
; Definitions
;---------------------
#define SWITCH    LATD,2  
#define LED0      PORTD,0
#define LED1	  PORTD,1

;---------------------
; Main Program
;--------------------
ORG 0X20
    MOVLW 0X00 ;moves 0x00 into Wreg
    MOVWF TRISD ;sets PORTD as an ouput

    MOVLW refTempInput ;moves refTempInput into Wreg
    MOVWF refTemp ;moves value of wreg into refTemp register
    MOVLW measuredTempInput ;moves measuredTempInput into Wreg
    MOVWF measuredTemp
    MOVLW 0XF0
    CPFSGT measuredTemp
	GOTO START
ELIMINATE:
    NEGF measuredTemp
    MOVLW 0X01
    ADDWF refTemp
     MOVLW refTemp ;moves value of refTempInput
   CPFSEQ measuredTemp
	GOTO COMPARE1
	GOTO LED_OFF1
COMPARE1:    
    CPFSLT measuredTemp
	GOTO LED_COOL1
    CPFSGT measuredTemp
	GOTO LED_HOT1
LED_OFF1:
    MOVLW 0x00
    MOVWF contReg
    MOVFF contReg,PORTD
    MOVLW 0X01
    SUBWF refTemp    
    GOTO NEXT
LED_HOT1:
    MOVLW 0x01
    MOVWF contReg
    MOVFF contReg,PORTD
    MOVLW 0X01
    SUBWF refTemp    
    GOTO NEXT
LED_COOL1:
    MOVLW 0X02
    MOVWF contReg
    MOVFF contReg,PORTD
    MOVLW 0X01
    SUBWF refTemp    
    GOTO NEXT
    
    
    
    
    
    
START:   
   MOVLW refTempInput ;moves value of refTempInput
   CPFSEQ measuredTemp
	GOTO COMPARE
	GOTO LED_OFF
COMPARE:    
    CPFSLT measuredTemp
	GOTO LED_COOL
    CPFSGT measuredTemp
	GOTO LED_HOT
LED_OFF:
    MOVLW 0x00
    MOVWF contReg
    MOVFF contReg,PORTD
    GOTO NEXT
LED_HOT:
    MOVLW 0x01
    MOVWF contReg
    MOVFF contReg,PORTD
    GOTO NEXT
LED_COOL:
    MOVLW 0X02
    MOVWF contReg
    MOVFF contReg,PORTD
    GOTO NEXT
NEXT: 
    MOVLW 0x64
    MOVFF 0X21, COUNTER
    CPFSLT COUNTER ;If wreg greater than measured temp skip next line
    GOTO COUNT_HUNDRED_M
    MOVLW 0XA
    CPFSLT COUNTER
    GOTO COUNT_TENS_M
    GOTO STORE_UNITS_M
COUNT_HUNDRED_M:
    INCF MHundred, 1
    MOVLW 100
    SUBWF COUNTER
    CPFSGT COUNTER 
    GOTO COUNT_TENS_M
    GOTO COUNT_HUNDRED_M
COUNT_TENS_M:
    INCF  MTens, 1
    MOVLW 10
    SUBWF COUNTER
    CPFSGT COUNTER
    GOTO STORE_UNITS_M ; 
    GOTO COUNT_TENS_M  ; Repeat subtraction
   
STORE_UNITS_M:
    MOVLW 0X0A
    CPFSEQ COUNTER
    GOTO RCONVERSION
            ; Store remaining units    
    SUBWF COUNTER
    INCF MTens,1
    MOVFF COUNTER, MUnits	    
	    
RCONVERSION:
    MOVFF COUNTER, MUnits
    MOVLW 0x64
    MOVFF 0X20, COUNTER2
    CPFSLT COUNTER2 ;If wreg greater than measured temp skip next line
    GOTO COUNT_HUNDRED_R
    MOVLW 0XA
    CPFSLT COUNTER2
    GOTO COUNT_TENS_R
    GOTO STORE_UNITS_R
COUNT_HUNDRED_R:
    INCF RHundred, 1
    MOVLW 100
    SUBWF COUNTER2
    CPFSGT COUNTER2 
    GOTO COUNT_TENS_R
    GOTO COUNT_HUNDRED_R
COUNT_TENS_R:
    INCF  RTens, 1
    MOVLW 10
    SUBWF COUNTER2; Subtract 10 from W register
    CPFSGT COUNTER2    ; If borrow, stop (W < 10)
    GOTO STORE_UNITS_R ; If borrow, store remaining units
    GOTO COUNT_TENS_R  ; Repeat subtraction

STORE_UNITS_R:
    MOVLW 0X0A
    CPFSEQ COUNTER2
    GOTO FINAL
            ; Store remaining units    
    SUBWF COUNTER2
    INCF RTens,1
    MOVFF COUNTER2, RUnits
    
FINAL:
    MOVFF COUNTER2, RUnits
END
    
    
    
    
    
    
    
    