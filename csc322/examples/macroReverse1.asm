; Bob Allen
; Macro example with loops inside
; Fall 2023

;;; Macro should be passed array name, and array length
%macro Reverse 2
	;;;; Push the integers onto the stack
	mov	ebx,%1
	mov	ecx,%2
pushTop:
	push	DWORD[ebx]
	add	ebx,4
	loop	pushTop


	;;;;; Pop the integers off of the stack
	mov	ebx,%1
	mov	ecx,%2
popTop:
	pop	DWORD [ebx]
	add	ebx,4
	loop	popTop
%endmacro

SECTION .data
nums:    dd 1,2,3,4,5,6,7,8,9,10
numsLen: EQU  (($ - nums)/4)	;;; NOTE, divide num bytes by 4 to get num dwords

vals:    dd 2,4,6
valsLen: EQU  (($ - vals)/4)	;;; NOTE, divide num bytes by 4 to get num dwords

SECTION .bss
; define uninitialized data here

SECTION .text
global _main
_main:

; put your code here.
break0:
	Reverse nums,numsLen
break1:
	Reverse vals,valsLen
lastBreak:

; Normal termination code
mov eax, 1
mov ebx, 0
int 80h
