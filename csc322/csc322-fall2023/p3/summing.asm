; Will King
; Prog 3
; CSC322 9/29/2023
; Summing all of the values in each array and then summing those totals

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQ
bArray:	DB	1,-2,3,-4,5
wArray: DW	100,200,300,400,500
dArray: DD	-322,-322h,-322q,-1833,-1833h
bArraySum: DB	0
wArraySum: DW	0
dArraySum: DD	0
grandTotal: DD	0
SECTION .bss
; define uninitialized data here

SECTION .text
global _main
_main:

; put your code here.
movsx ax, byte [bArray]
movsx bx, byte [bArray + 1]
add ax, bx
add [bArraySum], ax
movsx ax, byte [bArray + 2]
movsx bx, byte [bArray + 3]
add ax, bx
add [bArraySum], ax
mov ax, [bArray + 4]
add [bArraySum], bx

movsx eax, word [wArray]
movsx ebx, word [wArray + 1]
add eax, ebx
add [wArraySum], eax
movsx eax, word [wArray + 2]
movsx ebx, word [wArray + 3]
add eax, ebx
add [wArraySum], eax
movsx eax, word [wArray + 4]
add [wArraySum], eax

mov eax, dword [dArray]
mov ebx, dword [dArray + 1]
mov ecx, dword [dArray + 2]
mov edx, dword [dArray + 3]
add [dArraySum], eax
add [dArraySum], ebx
add [dArraySum], ecx
add [dArraySum], edx
mov eax, dword [dArray + 4]
add [dArraySum], eax

mov eax, [dArraySum]
mov ebx, [wArraySum]
mov cx, [bArraySum]
add [grandTotal], eax
add [grandTotal], ebx
add [grandTotal], cx
lastBreak:
; Normal termination code
mov eax, 1
mov ebx, 0
int 80h
