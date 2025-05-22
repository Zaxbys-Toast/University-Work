; Will King
; p10 - Happy Python
; 12/5/2023
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

%macro prtPython 0
	prt python, pythonSize
%endmacro

;;;;;  OpenFile needs permissions ecx:  0=readonly   101h = write
%macro OpenFile 1
        pusha
        mov     eax,5
        mov     ebx,fileName
        mov     ecx,%1
        int     80h
        mov     [fileDescriptor],eax
        popa
%endmacro

;;;; ReadFile from file needs 3 parms:  file descriptor (var), input buffer (var), length
%macro ReadFile 3
        pusha
        mov     eax,3 ;sys read
        mov     ebx,[%1]
        mov     ecx,%2
        mov     edx,%3
        int     80h
        popa
%endmacro

;;;; WriteFile needs 3 parms: file descriptor (var), buffer (var), length
%macro WriteFile 3
        pusha
        mov     eax,4
        mov     ebx,[%1]
        mov     ecx,%2
        mov     edx,%3
        int     80h
        popa
%endmacro

;;;; CloseFile needs no arguments
%macro CloseFile 0
        pusha
        mov     eax,6
        mov     ebx,[fileDescriptor]
        int     80h
        popa
%endmacro

STRUC py
	.stuff RESB 2
	.row RESB 2
	.semi RESB 1
	.col RESB 2
	.char RESB 2
	.size:
ENDSTRUC

%macro NormalTermination 0
        mov eax, 1
        mov ebx, 0
        int 80h
%endmacro
SECTION .data 
; define data/variables here.  Think DB, DW, DD, DQ
; Printing Stuff
python: db      1bh,'[02;40H@'
        db      1bh,'[02;41H*'
        db      1bh,'[02;42H*'
        db      1bh,'[02;43H*'
        db      1bh,'[02;44H*'
        db      1bh,'[02;45H*'
        db      1bh,'[02;46H+'
        db      1bh,'[02;47H '
pythonSize:  EQU  $-python

resetCursor:	db	1bh,'[01;01H'

cls:	db	1bh,'[2J'
clsLen:	EQU	$-cls

;;;;;;; Screen Pattern
screen: db      "********************************************************************************",0ah
        db      "*                          *                           *                       *",0ah
        db      "*      *************       *        *************      *       *********       *",0ah
        db      "*                          *                           *                       *",0ah
        db      "*                          *                           *                       *",0ah
        db      "*                          *                           *                       *",0ah
        db      "*                                                                              *",0ah
        db      "*           **************************        ***********************          *",0ah
        db      "*                                *               *                             *",0ah
        db      "*                                *     ***********                             *",0ah
        db      "*                          *     *               *     *                       *",0ah
        db      "*                          *     **********      *     *                       *",0ah
        db      "*                          *     *               *     *                       *",0ah
        db      "*                          *     *      **********     *                       *",0ah
        db      "*                          *                           *                       *",0ah
        db      "*                                                                              *",0ah
        db      "*           ***   ***   ***   ***   ***   ***   ***   ***   ***   ***          *",0ah
        db      "*                                                                              *",0ah
        db      "*            *     *     *     *     *     *     *     *     *     *           *",0ah
        db      "*               *     *     *     *     *     *     *     *     *              *",0ah
        db      "*            *     *     *     *     *  W  *     *     *     *     *           *",0ah
        db      "*               *     *     *     *     *     *     *     *     *              *",0ah
        db      "*            *     *     *     *     *     *     *     *     *     *           *",0ah
        db      "*               *     *     *     *     *     *     *     *     *              *",0ah
        db      "********************************************************************************",0ah
screenSize:     dd $-screen


; File Stuff
stdin   dd      0  ; used for read from stdin
stdout  dd      1  ; used for write to stdout
sleeping: db 'z'

sec:    dd 1,0

fileName:       db      './python.txt',0
fileDescriptor: dd      0

SECTION .bss
LEN     equ     1024
inputBuffer     RESB LEN
childPID        RESD 1

SECTION .bss
; define uninitialized data here

SECTION .text
global _main, _sleep1
_main:

; put your code here.
prt cls, clsLen
prtPython
prt resetCursor, 8
prt screen, screenSize

        ;;;;   FORK 2 PROCS
        mov     eax,2
        int     80h

        cmp     eax,0
        je      childProc
        mov     [childPID],eax

parent:

        call    _getCode
        WriteFile stdout, inputBuffer, 1
        cmp     al,'q'
        je      theEnd
	call movePython
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
        mov     eax,37
        mov     ebx,[childPID]
        mov     ecx,9  ; kill signal
        int     80h
        NormalTermination


;;;  GetCode - reads file to see what to do - no args passed in, returns char in AL
_getCode:
        OpenFile 0  ; readonly
        ReadFile        fileDescriptor, inputBuffer, 2
        CloseFile
        mov     al, BYTE [inputBuffer]
        ret



;;; Sleep function - sleeps for one second
_sleep1:
        pusha

        mov     eax,4
        mov     ebx,1
        mov     ecx,sleeping
        mov     edx,1
        int     80h

        mov     eax,162
        mov     ebx,sec
        mov     ecx,0
        int     80h
        popa
        ret

movePython:
	pusha

	cmp al, 'w'
	je north
	cmp al, 'a'
	je west
	cmp al, 's'
	je south
	cmp al, 'd'
	je east
	jmp en

	north:
		; Get the row and column of the Python pattern
    		mov eax, [python + py.row]
    		mov ebx, [python + py.col]

    		; Decrement the row of the Python pattern
    		mov ecx, [python + py.row]
    		dec ecx
    		mov [python + py.row], ecx

    		; Move the Python pattern upward by one line
    		mov esi, python            ; Pointer to the start of the Python pattern
    		add esi, py.size           ; Move esi to the end of the Python pattern
		mov ecx, 7
    		northTop:
        		sub esi, py.size       ; Move esi to the start of the previous line
        		mov edx, [esi + py.row] ; Get the row of the current line
        		mov edi, [esi + py.col] ; Get the column of the current line
	
        		mov [esi + py.row], eax ; Update the row with the previous row
        		mov [esi + py.col], ebx ; Update the column with the previous column

        		mov eax, edx           ; Move the current line's row to eax
        		mov ebx, edi           ; Move the current line's column to ebx

        		loop northTop

    		prtPython                   ; Print the updated Python pattern
    		jmp en                      ; Jump to the end
	west:
		; Get the row and column of the Python pattern
                mov eax, [python + py.row]
                mov ebx, [python + py.col]

                ; Decrement the col of the Python pattern
                mov ecx, [python + py.col]
                dec ecx
                mov [python + py.col], ecx

                ; Move the Python pattern up by one line
                mov esi, python            ; Pointer to the start of the Python pattern
                add esi, py.size           ; Move esi to the end of the Python pattern
                mov ecx, 7
                westTop:
                        sub esi, py.size       ; Move esi to the start of the previous line
                        mov edx, [esi + py.row] ; Get the row of the current line
                        mov edi, [esi + py.col] ; Get the column of the current line

                        mov [esi + py.row], eax ; Update the row with the previous row
                        mov [esi + py.col], ebx ; Update the column with the previous column

                        mov eax, edx           ; Move the current line's row to eax
                        mov ebx, edi           ; Move the current line's column to ebx

                        loop westTop

                prtPython                   ; Print the updated Python pattern
                

		jmp en
	south:
		; Get the row and column of the Python pattern
                mov eax, [python + py.row]
                mov ebx, [python + py.col]

                ; Increment the row of the Python pattern
                mov ecx, [python + py.row]
                inc ecx
                mov [python + py.row], ecx

                ; Move the Python pattern up by one line
                mov esi, python            ; Pointer to the start of the Python pattern
                add esi, py.size           ; Move esi to the end of the Python pattern
                mov ecx, 7
                southTop:
                        sub esi, py.size       ; Move esi to the start of the previous line
                        mov edx, [esi + py.row] ; Get the row of the current line
                        mov edi, [esi + py.col] ; Get the column of the current line

                        mov [esi + py.row], eax ; Update the row with the previous row
                        mov [esi + py.col], ebx ; Update the column with the previous column

                        mov eax, edx           ; Move the current line's row to eax
                        mov ebx, edi           ; Move the current line's column to ebx

                        loop southTop

                prtPython                   ; Print the updated Python pattern


		jmp en
	east:
		; Get the row and column of the Python pattern
                mov eax, [python + py.row]
                mov ebx, [python + py.col]

                ; Increment the col of the Python pattern
                mov ecx, [python + py.col]
                inc ecx
                mov [python + py.col], ecx

                ; Move the Python pattern up by one line
                mov esi, python            ; Pointer to the start of the Python pattern
                add esi, py.size           ; Move esi to the end of the Python pattern
                mov ecx, 7
                eastTop:
                        sub esi, py.size       ; Move esi to the start of the previous line
                        mov edx, [esi + py.row] ; Get the row of the current line
                        mov edi, [esi + py.col] ; Get the column of the current line

                        mov [esi + py.row], eax ; Update the row with the previous row
                        mov [esi + py.col], ebx ; Update the column with the previous column

                        mov eax, edx           ; Move the current line's row to eax
                        mov ebx, edi           ; Move the current line's column to ebx

                        loop eastTop

                prtPython                   ; Print the updated Python pattern

		jmp en
	en:
		ret
