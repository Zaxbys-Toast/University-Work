; Bob Allen
; Example of recursion with Fibonacci
; Fall 2023

SECTION .data
n:	   dd	47 gives our max fib for dd
theNthFib: dd	0

SECTION .text
global _main, _fib
_main:

;;;;;;;;;;;;;;;;;;;  	 Parameter passing for _fib: 
;;;;;;;;;;;;;;;;;;;      input: push n on stack 
;;;;;;;;;;;;;;;;;;;      output: pop fib(n) off stack
push DWORD [n]
call _fib
pop  DWORD [theNthFib]

lastBreak:


; Normal termination code
mov eax, 1
mov ebx, 0
int 80h


;;;;;;;;;;;;;;;;; Fib ;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;      input: n was pushed on stack 
;;;;;;;            output: fib(n) replaced on stack
;;;;;;;	           (i.e. replaces n with Fib(n))

_fib:
	push ebx  ;; Save because we use within
	push ecx  ;; Save because we use within

	mov  ebx,[esp+12] ; get N: skip ecx, ebc, ret addr
	cmp  ebx,1
	jbe  stopRecur  ;;;;;; Fib(1) is 1 and Fib(0) is 0
	;;;;;; the recursive calls
	dec  ebx 	;;; N-1
	push ebx
	call _fib	;;; fib(N-1)
	pop  ecx	;;; hold fib(n-1) to add to fib(n-2)

	dec  ebx	;;; N-2
	push ebx
	call _fib	;;; fib(N-2)
	pop  ebx
	add  ebx,ecx	;;; fib(n-1) + fib(n-2)
	mov  DWORD [esp+12],ebx  ;;;  Replace N with fib(N) on stack 
stopRecur:
	pop ecx  ;; Restore original value
	pop ebx  ;; Restore original value
	ret


















