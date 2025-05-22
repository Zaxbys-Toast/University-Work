; NAME
; Assignment
; Date
; Etc...

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQ
a1: DB 11
b1: DW 11b
c1: DD 11h
d1: DQ 11q
e1: DW -5
f1: DB 'CSC322'
g1: DB 'Howdy'
h1: DW 'Howdy'
i1: DB 1,2,3
j1: DD 10,11,12,14
a2: DW 11,13,15,17
b2: DB 11,13,15,18
c2: DD 100,200,300
d2: DQ 12345h
a3: DB -50
b3: DW -45
c3: DB -30
d3: DW -25
e3: DD -20
a4: DB 'Bears'
b4: DD 100
c4: DW 0
d4: DB 'Go '
e4: DB 'Mercer!'
a5: DW 100
b5: DW 100h
c5: DW 100b
d5: DW 100q
e5: DW 100d
SECTION .bss
; define uninitialized data here

SECTION .text
global _main
_main:

; put your code here.



; Normal termination code
mov eax, 1
mov ebx, 0
int 80h
