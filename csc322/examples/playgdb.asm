; NAME
; Assignment
; Date
; Etc...

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQrray:		DB		1,-2,3,-4,5
wArray:		DW		100,200,300,400,500
dArray:		DD		-322,-322h,-322q,-1833,-1833h
bArraySum:	DB		0
wArraySum:	DW		0
dArraySum:	DD		0
grandTotal:	DD		0

SECTION .bss
; define uninitialized data here

SECTION .text
global _main
_main:

; put your code here.
mov al, [bArray]
mov bx, [bArray]
mov cx, [wArray]
mov edx, [dArray]
lastBreak:

; Normal termination code
mov eax, 1
mov ebx, 0
int 80h
