;---------------------
; Title: Heating and Cooling Control System
;---------------------
; Program Details:
; The purpose of this program is to determine whether 

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

;---------------------
; Program Inputs
;---------------------
#define measuredTempInput 45 ;input measuered value in decimal
#define refTempInput 25 ;input refereence value in decimal
 
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
    MOVLW refTempInput ;moves refTempInput into Wreg
    MOVWF refTemp ;moves value of wreg into refTemp register
    MOVLW measuredTempInput ;moves measuredTempInput into Wreg
    MOVWF measuredTemp ;moves value of wreg into measuredTemp register
    MOVLW 0X00 ;moves 0x00 into Wreg
    MOVWF TRISD ;sets PORTD as an ouput
    MOVLW refTempInput ;moves value of refTempInput
    
   CPFSEQ measuredTemp
	GOTO LED_OFF
   CPFSGT measuredTemp
	GOTO LED_HOT
    CPFSLT measuredTemp
	GOTO LED_COOL
LED_OFF:
    MOVLW 0x00
    MOVWF contReg
    MOVFF contReg,PORTD
LED_HOT:
    MOVLW 0x01
    MOVWF contReg
    MOVFF contReg,PORTD
LED_COOL:
    MOVLW 0X02
    MOVWF contReg
    MOVFF contReg,PORTD

    
    
    MOVLW measuredTemp
COUNT_TENS_M:
    SUBLW 10           ; Subtract 10 from W register
    BTFSS STATUS,0    ; If borrow, stop (W < 10)
    GOTO STORE_UNITS_M ; If borrow, store remaining units

    INCF  MTens, F      ; Increment tens counter
    GOTO COUNT_TENS_M  ; Repeat subtraction

STORE_UNITS_M:
    ADDLW 10           ; Add back the last subtraction
    MOVWF  MUnits        ; Store units
    RETURN    