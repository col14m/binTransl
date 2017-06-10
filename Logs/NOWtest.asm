global _start
extern printf
extern scanf
section .data
val: dd 0.0      
formatPrint  db '%lg', 10, 0
formatScan  db '%lg',0
section .text
_start:
finit
;----PUSH VAL----
fld qword 0xC1340000
;----PUSH VAL----
fld qword 0xC1B26666
;----ADD----
fadd
;----SUB----
fsub
;----MUL----
fmul
;----SQRT----
fsqrt
;----PUSHR AX----
movd [val], eax
fld dword [val]
;----POPR AX----
fstp dword[val]
movd eax, [val]
;----OUT----
mov rdi, formatPrint
mov rax, 1
call printf
;----IN----
push rbp
mov rbp, rsp
sub rsp, 16
xor eax, eax
pxor    xmm0, xmm0
movsd   qword  [rbp-16], xmm0
lea rsi, [rbp-16]
mov rdi, formatScan
mov rax, 0
call scanf
sub rsp, 24
;----Exit----
mov rax, 60
mov rdi, 0
syscall
