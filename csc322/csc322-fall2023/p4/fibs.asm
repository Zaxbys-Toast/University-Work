; NAME
; Assignment
; Date
; Etc...

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQ
sum: DB 0
SECTION .bss
; define uninitialized data here
Fibs:	RESD 16
SECTION .text
global _main
_main:
; put your code here.
mov edx, 0
mov dword [Fibs], 0
mov dword [Fibs + 4], 1
mov ecx, 14
l1:
	
	mov eax, [Fibs + edx]
	mov ebx, [Fibs + edx + 4]
	add ebx, eax
	mov [Fibs + 8 + edx], ebx
	add edx, 4
	dec ecx
	cmp ecx, 0
	jz lastBreak
	jmp l1
; Normal termination code
lastBreak:
mov eax, 1
mov ebx, 0
int 80h
