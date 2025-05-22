; Bob Allen
; CSC 322 Fall 2023
; Play with FORKs
;  and with FILES

;;;;;  OpenFile needs permissions ecx:  0=readonly   101h = write
%macro OpenFile 1
	pusha
	mov	eax,5
	mov	ebx,fileName
	mov	ecx,%1  
	int	80h
	mov	[fileDescriptor],eax
	popa
%endmacro

;;;; ReadFile from file needs 3 parms:  file descriptor (var), input buffer (var), length
%macro ReadFile 3
	pusha
        mov     eax,3 ;sys read
        mov     ebx,[%1]
	mov	ecx,%2
        mov     edx,%3
        int     80h
	popa
%endmacro

;;;; WriteFile needs 3 parms: file descriptor (var), buffer (var), length
%macro WriteFile 3
	pusha
	mov	eax,4
	mov	ebx,[%1]
	mov	ecx,%2
	mov	edx,%3
	int	80h
	popa
%endmacro

;;;; CloseFile needs no arguments
%macro CloseFile 0
	pusha
	mov	eax,6
	mov	ebx,[fileDescriptor]
	int	80h
	popa
%endmacro

;;;;; NormalTermination needs no args
%macro NormalTermination 0
	mov eax, 1
	mov ebx, 0
	int 80h
%endmacro

SECTION .data
; define data/variables here.  Think DB, DW, DD, DQ

stdin	dd	0  ; used for read from stdin
stdout	dd	1  ; used for write to stdout
sleeping: db 'z'

sec:	dd 1,0

fileName:	db	'./bob.txt',0
fileDescriptor: dd	0

SECTION .bss
LEN	equ	1024
inputBuffer	RESB LEN
childPID	RESD 1

SECTION .text
global _main, _sleep1
_main:

	;;;;   FORK 2 PROCS
	mov	eax,2
	int	80h

	cmp	eax,0
	je	childProc
	mov	[childPID],eax

parent:

	call	_getCode
	WriteFile stdout, inputBuffer, 1
	cmp	al,'q'
	je	theEnd

	; sleep one second
time2sleep:
	call _sleep1
	jmp parent

childProc:
	
	ReadFile stdin, inputBuffer, LEN

	;; Open a file for communication
	OpenFile 101h  ; for writing

	;;; write  something to  bob.txt
	WriteFile fileDescriptor, inputBuffer, 1

	;;;  close the file
	CloseFile

	jmp childProc

; Normal termination code
theEnd:
	;;;;;;  Kill the child process
	mov	eax,37
	mov	ebx,[childPID]
	mov	ecx,9  ; kill signal
	int 	80h
	NormalTermination


;;;  GetCode - reads file to see what to do - no args passed in, returns char in AL
_getCode:
	OpenFile 0  ; readonly
	ReadFile	fileDescriptor, inputBuffer, 2
	CloseFile
	mov	al, BYTE [inputBuffer]
	ret



;;; Sleep function - sleeps for one second
_sleep1:
        pusha

	mov	eax,4
	mov	ebx,1
	mov	ecx,sleeping
	mov	edx,1
	int	80h

        mov     eax,162
        mov     ebx,sec
        mov     ecx,0
        int     80h
        popa
        ret

