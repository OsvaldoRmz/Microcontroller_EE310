;---------------------
; Title: Heating and Cooling Control System
;---------------------
; Program Details:
; The purpose of this program is to create a counter via a seven segment display that allows the user to increment and decrement by 1 and reset to zero when both inputs are pressed

; Inputs: SWITCH1, SWITCH2 
; Outputs: PORTD
; Date: March 20 2025
; File Dependencies / Libraries: #include "C:\Users\osval\MPLABXProjects\SevenSegmentCounter.X\AssemblyConfig.inc"
; Compiler: xc8, 2.46
; Author: Osvaldo Ramirez
; Versions:
;       V1.0 3/20/25 - First Version



;---------------------
; Initialization 
;---------------------
#include "C:\Users\osval\MPLABXProjects\SevenSegmentCounter.X\AssemblyConfig.inc"


#include <xc.inc>
PSECT absdata,abs,ovrld ;do not change
;---------------------
; Program Inputs
;---------------------
#define SWITCH1 LATC,0
#define SWITCH2 LATC,1
;---------------------
; Program Constants
;---------------------

REGO EQU 0h
;---------------------
; Definitions
;---------------------
#define SEVENSEG      PORTD



;---------------------
; Main Program
;--------------------
 
 ORG 0x20
  
MAIN:
   RCALL _setupPortD
   RCALL _setupPortC

LOOP:
    MOVF PORTC, W  ; Read button states
    ANDLW 0x03     ; Mask out bits 0 and 1 (keep only button states)
    CPFSEQ 0x00    ; Check if neither button is pressed
    GOTO CHECK_BUTTONS
    GOTO LOOP      ; If neither is pressed, loop again

CHECK_BUTTONS:
    MOVF PORTD, W  ; Read button states again
    ANDLW 0x03     ; Mask only bits 0 and 1

    CPFSEQ 0x03    ; If both buttons are pressed, reset counter
    GOTO RESETT

    CPFSEQ 0x01    ; If only Button A is pressed, increment
    GOTO DECREMENT

    CPFSEQ 0x02    ; If only Button B is pressed, decrement
    GOTO INCREMENT

    GOTO LOOP      ; If nothing matches, loop again

INCREMENT:
    INCF REGO, F    ; Increase REGO (mod 16)
    MOVLW 0x10
    CPFSGT REGO     ; If REGO >= 16, reset to 0
    CLRF REGO
    GOTO DISPLAY

DECREMENT:
    DECF REGO, F    ; Decrease REGO
    BTFSC STATUS, 2 ; If zero flag is set, set to 15
    MOVLW 0x0F
    MOVWF REGO
    GOTO DISPLAY

RESETT:
    CLRF REGO       ; Reset REGO to 0
    GOTO DISPLAY

DISPLAY:
    MOVLW 0x00       ; Upper byte 
    MOVWF TBLPTRU

    MOVLW 0x00       ; High byte 
    MOVWF TBLPTRH

    MOVLW 0x00       ; Low byte 
    MOVWF TBLPTRL


    MOVF REGO, W          ; Load number to display
    ADDWF TBLPTRL, F      ; Add offset to table pointer

    TBLRD*                ; Read value from lookup table
    MOVFF TABLAT, PORTD   ; Send to 7-segment display

    GOTO LOOP             ; Repeat forever
_setupPortD:
    BANKSEL	PORTD ; ; Set PORTD as output (for 7-segment display)
    CLRF	PORTD ;
    BANKSEL	LATD ;Data Latch
    CLRF	LATD ;
    BANKSEL	ANSELD ;
    CLRF	ANSELD ;digital I/O
    BANKSEL	TRISD ;
    MOVLW	0X00 ;
    MOVWF	TRISD ;and set RD0 as ouput
    RETURN
 
_setupPortC:
    BANKSEL	PORTC ;
    CLRF	PORTC ;
    BANKSEL	LATC ;Data Latch
    CLRF	LATC ;
    BANKSEL	ANSELC ;
    CLRF	ANSELC ;digital I/O
    BANKSEL	TRISC ;
    MOVLW	0X03 ;Set PORTC,0 & PORTC,1 as inputs (buttons)
    MOVWF	TRISC
    RETURN    

    ORG 100h
CODEADDR:
    DB 0xC0, 0xF9, 0xA4, 0xB0, 0x99  ; LED codes for 0-4
    DB 0x92, 0x82, 0xF8, 0x80, 0x98  ; LED codes for 5-9
    DB 0x88, 0x83, 0xC6, 0xA1, 0x86  ; LED codes for A-E
    DB 0x8E ;LED code for F
    END