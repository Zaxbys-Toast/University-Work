; Will King
; Matrix Management
; 10/19/2023
ROWS:  	    EQU	5	; defines a constant ROWS set to 5.
COLS:       EQU	7	; defines a constant COLS set to 7.

SECTION .bss
RowSums:	RESD ROWS
ColSums:	RESD COLS
Sum:		RESD 1
saveEcx: 	RESD 1
SECTION .data
MyMatrix: 	dd	 1,  2,  3,  4,  5,  6,  7
	    	dd	 8,  9, 10, 11, 12, 13, 14
		dd	15, 16, 17, 18, 19, 20, 21
		dd	22, 23, 24, 25, 26, 27, 28
		dd	29, 30, 31, 32, 33, 34, 35

SECTION .text
global _main
_main:

; put your code here.
mov esi, MyMatrix
mov edi, RowSums
xor eax, eax
mov ecx, ROWS

outerRow:
	mov [saveEcx], ecx
	mov ecx, COLS
innerRow:
	add dword eax, [esi]
	add esi, 4 
loop innerRow
	mov [edi], eax
	xor eax, eax
	add edi, 4
	add esi, 4

	loop outerRow
mov esi, MyMatrix 
mov edi, ColSums
mov ecx, COLS
outerCol:
	mov [saveEcx], ecx
	mov ecx, ROWS
innerCol:
	add eax, [esi]
	add esi, COLS * 4
loop innerCol
	mov esi, MyMatrix
	inc dword esi	
	mov eax, [edi]
	add edi, 4
	xor eax, eax
loop outerCol
lastBreak:
; Normal termination code
mov eax, 1
mov ebx, 0
int 80h
