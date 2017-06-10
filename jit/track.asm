section .bss




section .text
    global _start

_start:
    


    mov edi, dword [val] 
    call track

   
    ;Exit (0) 
    mov rax, 60
    mov rdi, 0
    syscall

track:
    push rbp
    mov rbp, rsp
    finit

    mov dword [rbp - 4], edi
    fld dword [rbp - 4]
    fsin
    fstp dword [rbp - 4]
    mov eax, dword [rbp - 4]
    pxor   xmm0,xmm0
    cvtsi2sd xmm0,eax

    pop rbp
    ret
section .data

val  dd 3.14
