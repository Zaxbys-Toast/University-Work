; Bob Allen
; CSC 322 
; Fall 2023
; Playing with addressing

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQ
a1:	db	1,2,3,4,5
a2:	dw	1,2,3,4,5


SECTION .bss
; define uninitialized data here
a3:	RESD 5

SECTION .text
global _main
_main:

; Let's reverse a1
begin:
	mov ah,[a1]
	mov al,[a1+4]
	mov [a1],al
	mov [a1+4],ah
	mov ah,[a1+1]
	mov al,[a1+3]
	mov [a1+1],al
	mov [a1+3],ah
rev1:

; let's reverse a2 using pointers
	mov ebx,a2	; address of a1 in ebx
	mov ax,[ebx]
	mov cx,[ebx+8]
	mov [ebx],cx
	mov [ebx+8],ax
	add ebx,2	; ebx pints to second element
	mov ax,[ebx]
	mov cx,[ebx+4]
	mov [ebx],cx
	mov [ebx+4],ax
rev2:

; let's store a2 as dd data in a3
;  (convert words to dwords and store in array)
;  esi and edi are dword regs used for addressing mem
;  
	mov esi,a2	; source index
	mov edi,a3	; dest index
	movsx eax,WORD[esi]
	mov [edi],eax
	add esi,2	; next word in array a2
	add edi,4	; next dword in array a3
	movsx eax,WORD[esi]
	mov [edi],eax
	add esi,2	; next word in array a2
	add edi,4	; next dword in array a3
	movsx eax,WORD[esi]
	mov [edi],eax
	add esi,2	; next word in array a2
	add edi,4	; next dword in array a3
	movsx eax,WORD[esi]
	mov [edi],eax
	add esi,2	; next word in array a2
	add edi,4	; next dword in array a3
	movsx eax,WORD[esi]
	mov [edi],eax
	add esi,2	; next word in array a2
	add edi,4	; next dword in array a3

lastBreak:


; Normal termination code
mov eax, 1
mov ebx, 0
int 80h














