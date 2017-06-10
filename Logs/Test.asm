section .text

global _start
_start:
    ;fld    qword [double_value1]   ;push single_value1 to fpu stack
    ;fld    qword [double_value1]   ;push double_value2 to fpu stack
    ;fadd ;st0 := st1 + st0

    .Next:

    ;mov dword [val], eax
    ;mov dword [val], ebx
    ;mov dword [val], ecx
    ;mov dword [val], edx
    ;mov dword [val], esi 
    fld dword [val]
    fld dword [val]
    fcom
    fstsw ax          ;copy the Status Word containing the result to AX
    fwait             ;insure the previous instruction is completed
    sahf              ;transfer the condition codes to the CPU's flag register
    je .Next
    fstp dword [val]
    mov ebx, dword [val]
    mov ecx, dword [val]
    mov edx, dword [val]
    mov esi, dword [val]
    push rbx
    push rcx
    push rdx
    pop rbx
    pop rcx
    pop rdx
    ret
    
    ;mov rbx, 60
    ;mov rdi, 0
    mov ebx, eax
    jne .Next
    syscall
    mov eax, 60
    mov edi, 0
    syscall

;section .data
   ; format  db     '%lg', 10, 0
   double_value1   dq 102.35
   val dw 10
   ; double_value2   dq 12.34
