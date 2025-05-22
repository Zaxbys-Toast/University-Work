; Will King
; Max Fibonnachi
; 10/16/2023
; Etc...

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQ
sum: DB 0
SECTION .bss
; define uninitialized data here
MaxFib:		RESD 1
FibCount:	RESW 1
SECTION .text
global _main
_main:
; put your code here.
mov eax, 0
mov ebx, 1
mov ecx, 0
mov word [FibCount], 2

jmp checkLoop

l:	
	inc word [FibCount]
	mov ecx, eax
checkLoop:
	mov ecx, ebx
	add ebx, eax
	jnc l
mov [MaxFib], ecx
; Normal termination code
lastBreak:
mov eax, 1
mov ebx, 0
int 80h
