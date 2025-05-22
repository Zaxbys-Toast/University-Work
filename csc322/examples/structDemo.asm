; NAME:  Bob Allen
; Struc Demo adding Scores
; Date: Fall 2023


; Constant for Size of array of structs
LEN:	EQU	5

; Define Structure for character on screen
STRUC scoreStruct
	.name	RESB 11 ; Name plus newline
	.test1	RESW 1  ; Test 1's score
	.test2	RESW 1  ; Test 2's score
	.test3	RESW 1  ; Test 3's score
	.test4	RESW 1  ; Test 4's score
	.avg	RESW 1	; Average for 4 tests
	.letter	RESB 2  ; Letter Grade plus newline
	.size	RESW 1
ENDSTRUC

SECTION .data
; Create an array of structs: formatted like the print interrupt uses.
gradebook:	db "Robert    ",10
		dw 50,60,70,80
		dw 0
		db '-',10
		db "Bob       ",10
		dw 100,90,80,70
		dw 0
		db '-',10
		db "Bobby     ",10
		dw 75,95,85,75
		dw 0
		db '-',10
		db "Robbie    ",10
		dw 100,100,100,100
		dw 0
		db '-',10
		db "Allen     ",10
		dw 10,20,30,40
		dw 0
		db '-',10

SECTION .bss

SECTION .text
global _main
_main:

;;;;  Loop over the LEN student records
;;;;  And average the four tests and
;;;;  Assign a letter grade
	mov ecx,LEN
	mov esi,gradebook   ;;; points to the array of structs
top:

	;;;; Some processing for each struc here

	add esi,scoreStruct.size
	loop top

lastBreak:
; Normal termination code
mov eax, 1
mov ebx, 0
int 80h
;;;;;;;;;;;;;;;;;;;;; END OF MAIN ;;;;;;;;;;;;;;;;;;;;;;;;;;;;
