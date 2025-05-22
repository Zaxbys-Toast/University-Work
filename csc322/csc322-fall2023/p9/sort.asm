; Will King
; Program 9: Sort Array
; 11/13/2023
; Etc...


%macro prt 2
	pusha
	mov eax, 4
	mov ebx, 1
	mov ecx, %1
	mov edx, %2
	int 80h
	popa
%endmacro

SECTION	.data
; define data/variables here.  Think DB, DW, DD, DQ
nums:	dw	 2000, 3000, 0, 65535, 0, 1, 2, 3, 100
numslen: 	EQU 	($-nums)
title: db "Will's Array Sorting Program", 10, 0
header: db "Original Array", 10, 0
titlelen:	EQU	($-title)
headerlen:	EQU	($-header)
SECTION .bss
; define uninitialized data here

SECTION .text
global _main
_main:
; put your code here.
; Print title, "Will's Sorting Program"
prt title, titlelen
; Print header, "Original Array"
prt header, headerlen
; Print Original Array
conversion_loop:
    mov eax, [esi]      ; Load the current number from the array
    call intToString    ; Convert it to a string
    mov edi, eax        ; Store the address of the converted string in edi
    mov ebx, 4          ; File descriptor (stdout)
    mov ecx, edi        ; Address of the string to print
    mov edx, 2          ; Length of the string (assuming each number is a word)
    int 0x80            ; Print the converted string
    add esi, 2          ; Move to the next word in the array
    loop conversion_loop; Continue until all elements are converted and printed
mov edi, nums          ; Set edi to point to the start of the converted strings
prt edi, numslen / 2   ; Print the converted stringsss
;normal termination code
mov eax, 1
mov ebx, 0
	
; Normal termination code
mov eax, 1
mov ebx, 0
int 80h

intToString:
	pusha
	xor ebx, ebx
	pushLoop:
		xor edx, edx
		mov ecx, 10
		div ecx
		add edx, 48
		push edx
		inc ebx
		cmp eax, 0
		jnz pushLoop
	popLoop:
		pop eax
		mov edi, eax
		dec ebx
		cmp ebx, 0
		jg popLoop
	ret
	
	
	
	
	
	






