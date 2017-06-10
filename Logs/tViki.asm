global _start

      extern printf
      extern scanf
section .data
    val: dd 1.57  ;declare quad word (double precision)
    val1: dq 3.14  ;declare quad word (double precision)
    format  db     '%f', 10, 0
    format1  db     '%f',0

section .bss
    res: resq 1     ;reserve 1 quad word for result

section .text
    _start:

    push	rbp
	mov	rbp, rsp
	sub	rsp, 16
	;mov	rax, QWORD PTR fs:40
	mov	qword [rbp-8], rax
    ;mov	qword [rbp-8], rax
	xor	eax, eax
	pxor	xmm0, xmm0
	movss	dword  [rbp-12], xmm0
	;lea	rax, [rbp-16]
    
	;mov	rsi, rax
    lea rsi, [rbp-12]
	mov rdi, format1
    mov rax, 0
    call scanf
    add rsp, 16
    pop rbp
    movss dword [val], xmm0
    ;movss	xmm0, dword [rbp-12]
	cvtss2sd	xmm0, xmm0

    ;sub rsp, 16
    ;fld qword [val] ;load value into st0
    ;fld qword [val1] ;load value into st0
   ; fdiv           ;compute square root of st0 and store in st
   ; fst qword [val]
    ;movsd xmm0, qword [val]
   ; fst qword [res] ;store st0 in result
	mov rdi, format
    mov rax, 1
    call printf

    ;mov rsp, rbp
    ;push rbp
    ;Exit (0) 
    mov rax, 60
    mov rdi, 0
    syscall

    ;end program

