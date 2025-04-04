;---------------------
; Title: Seven Segment Counter
;---------------------
; Program Details:
; The purpose of this program is to create a counter via a seven segment display that allows the user to increment and decrement by 1 and reset to zero when both inputs are on

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
#include "./AssemblyConfig.inc"


#include <xc.inc>
PSECT absdata,abs,ovrld ;do not change
;---------------------
; Program Inputs
;---------------------

Inner_loop  equ 2500 // in decimal
Outer_loop  equ 1500
;---------------------
; Program Constants
;---------------------

COUNT EQU 20h
COUNT2 EQU 24h
REG21 EQU 21h   // in HEX
REG22 EQU 22h
;--------------------
; Definitions
;---------------------



;---------------------
; Main Program
;--------------------
 
ORG 0x20
   
MAIN:
   CALL _setupPortD
   CALL _setupPortB
   MOVLW 0X3F
   MOVWF PORTD
   CLRF COUNT
LOOP: ; Read button states
    CALL loopDelay
    CALL ZEROCHECK
    BTFSC PORTB,0
    GOTO CHECK_BUTTONS   ; Check if neither button is pressed
    BTFSC PORTB,1
    GOTO CHECK_BUTTONS
    
    GOTO LOOP      
ZEROCHECK:
    MOVLW 0X03
    CPFSEQ PORTB
    RETURN
    MOVWF PORTD
    CLRF COUNT
    CLRF COUNT2          
    GOTO DISPLAY 
    
CHECK_BUTTONS:
    CALL loopDelay2
    ; Read button states again
    

    BTFSS PORTB,0    ; If only Button A is pressed, increment
    GOTO DECREMENT

    BTFSS PORTB,1    ; If only Button B is pressed, decrement
    GOTO INCREMENT

    GOTO LOOP      ; If nothing matches, loop again
INCREMENT:
    CALL loopDelay
    INCF COUNT, F    ; Increase REGO (mod 16)
    MOVLW 0x10
    CPFSLT COUNT     ; If REGO >= 16, reset to 0
    CLRF COUNT
    GOTO DISPLAY

DECREMENT:
    CALL loopDelay
    DECF COUNT, F; Decrease REGO
    BTFSC STATUS, 4 ; If zero flag is set, set to 15
    GOTO ZERO1
    
    GOTO DISPLAY
    
ZERO1:
    MOVLW 0x0F
    MOVWF COUNT
    GOTO DISPLAY

DISPLAY:

    MOVLW 0X00
    MOVWF TBLPTRU
    MOVLW 0X0A
    MOVWF TBLPTRH
    MOVLW 0X00
    MOVWF TBLPTRL
    CALL TBLPTRCOUNT
    MOVF COUNT2, W          ; Load number to display
    ADDWF TBLPTRL, F      ; Add offset to table pointer

    TBLRD*                ; Read value from lookup table
    MOVFF TABLAT, PORTD   ; Send to 7-segment display
    CALL loopDelay3
    GOTO LOOP             ; Repeat forever
TBLPTRCOUNT:
    MOVF COUNT,W
    MULLW 0X02
    MOVF PRODL, W
    MOVWF COUNT2
    RETURN
_setupPortD:
    BANKSEL	PORTD ; ; Set PORTD as output (for 7-segment display)
    CLRF	PORTD ;
    BANKSEL	LATD ;Data Latch
    CLRF	LATD ;
    BANKSEL	ANSELD ;
    CLRF	ANSELD ;digital I/O
    BANKSEL	TRISD ;
    MOVLW	0X00 ;
    MOVWF	TRISD ;and set RD as ouput
    RETURN
 
_setupPortB:
    BANKSEL	PORTB ;
    CLRF	PORTB ;
    BANKSEL	LATB ;Data Latch
    CLRF	LATB ;
    BANKSEL	ANSELB ;
    CLRF	ANSELB ;digital I/O
    BANKSEL	TRISB ;
    MOVLW	0X03 ;Set PORTb,0 & PORTb,1 as inputs (buttons)
    MOVWF	TRISB
    RETURN
    ;-----The Delay Subroutine    
loopDelay: 
    MOVLW       Inner_loop
    MOVWF       REG21
    MOVLW       Outer_loop
    MOVWF       REG22
_loop1:
    DECF        REG21,1
    BNZ         _loop1
    MOVLW       Inner_loop ; Re-initialize the inner loop for when the outer loop decrements.
    MOVWF       REG21
    DECF        REG22,1 // outer loop
    BNZ        _loop1
    RETURN
loopDelay2: 
    MOVLW       Inner_loop
    MOVWF       REG21
    MOVLW       Outer_loop
    MOVWF       REG22
_loop2:
    DECF        REG21,1
    BNZ         _loop2
    MOVLW       Inner_loop ; Re-initialize the inner loop for when the outer loop decrements.
    MOVWF       REG21
    DECF        REG22,1 // outer loop
    BNZ        _loop2
    RETURN
loopDelay3: 
    MOVLW       Inner_loop
    MOVWF       REG21
    MOVLW       Outer_loop
    MOVWF       REG22
_loop3:
    DECF        REG21,1
    BNZ         _loop3
    MOVLW       Inner_loop ; Re-initialize the inner loop for when the outer loop decrements.
    MOVWF       REG21
    DECF        REG22,1 // outer loop
    BNZ        _loop3
    RETURN
    
    ORG 0X0A00
NUMBERS:
  
    RETLW   0x3F ;0
    RETLW   0X06 ;1
    RETLW   0X5B ;2
    RETLW   0X4F ;3
    RETLW   0X66 ;4
    RETLW   0x6D ;5
    RETLW   0X7D ;6
    RETLW   0X07 ;7
    RETLW   0X7F ;8
    RETLW   0X6F ;9
    RETLW   0X77 ;A
    RETLW   0X7C ;B
    RETLW   0X39 ;C
    RETLW   0X5E ;D
    RETLW   0X79 ;E
    RETLW   0X71 ;F
    END