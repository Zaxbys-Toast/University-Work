; NAME Will King
; Assignment Reverse Array
; Date 11/8/23
; Etc...

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQ
array1: dd      1,2,3,4,5
len1:   EQU     ($-array1)


array2: dd      -10, -9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9
len2:   EQU     ($-array2)


array3: dd  0,10,20,30,40,50,60,70,80,90
  dd  100,110,120,130,140,150,160,170,180,190
  dd  200,210,220,230,240,250,260,270,280,290
  dd  300,310,320,330,340,350,360,370,380,390
  dd  400,410,420,430,440,450,460,470,480,490,500
len3:   EQU     ($-array3)
SECTION .bss
; define uninitialized data here

SECTION .text
global _main
_main:

; put your code here.

mov eax, array1
mov dword ebx, len1/4
call revArray



lastBreak:
; Normal termination code
mov eax, 1
mov ebx, 0
int 80h

;uses eax as the memory address for the array
;uses ebx as the length of the array
revArray:
;preserve the values in the registers that are getting used
	push edi
	push ecx
	mov edi, 0
	mov ecx, ebx
;loop through the array and push everything onto the stack
	loopPush:
		push dword [eax + edi]
		add dword edi, 4
		loop loopPush
	mov edi, 0
	mov ecx, ebx
;loop through the array and pop all of the values back into the array. Will be reversed
	loopPop:
		pop dword [eax + edi]
		add dword edi, 4
		loop loopPop
;restore the register values
	pop ecx
	pop edi
	ret
