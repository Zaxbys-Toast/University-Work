; Bob Allen
; Demo FORK
; Fall 2023	
; CSC 322

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQ

parentMSG: db "Parent",10,0
pLEN:	   equ $-parentMSG

childMSG:  db "Children are more fun!",10,0
cLEN:	   equ $-childMSG

sec:	dd 1,0	 ;; struct for sleep on second

SECTION .bss

SECTION .text
global _main, _sleep1
_main:

	;;;;   FORK 2 PROCS
	mov	eax,2
	int	80h

	;;;;;;;;;;;;;;;;;;;;;;  Creates two processes, same code,
	;;;;;;;;;;;;;;;;;;;;;;   but returns zero to new proc, and the procID of child to parent
	cmp	eax,0
	je	childProc

parent:

	;;; print parent message
	mov	eax,4
	mov	ebx,1
	mov	ecx,parentMSG
	mov	edx,pLEN
	int	80h

	; sleep one second
	call _sleep1
	jmp parent

childProc:
	;;; print child  message
	mov	eax,4
	mov	ebx,1
	mov	ecx,childMSG
	mov	edx,cLEN
	int	80h

	; sleep two seconds
	call _sleep1
	call _sleep1
	jmp childProc

byebye:
; Normal termination code
mov eax, 1
mov ebx, 0
int 80h

_sleep1:
        pusha
        mov     eax,162
        mov     ebx,sec
        mov     ecx,0
        int     80h
        popa
        ret

