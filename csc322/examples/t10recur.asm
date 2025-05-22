; NAME
; Assignment
; Date
; Etc...

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQ

num: dd 123

SECTION .bss
; define uninitialized data here

SECTION .text
global _main
_main:

; give regs some init values - don't destroy these!
	mov eax,1
	mov ebx,2
	mov ecx,3
	mov edx,4
before:
	push dword [num]
	call times10
	pop  dword [num]

lastBreak:

; Normal termination code
mov eax, 1
mov ebx, 0
int 80h


times10:
	push eax
	push ebx
	mov eax,[esp+12]
	mov ebx,eax
	shl ebx,1
	shl eax,3
	add eax,ebx
	mov [esp+12],eax
	pop ebx
	pop eax
	ret
