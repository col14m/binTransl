	.file	"test1.c"
	.intel_syntax noprefix
	.section	.rodata
.LC1:
	.string	"%f"
.LC2:
	.string	"%f\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR [rbp-8], rax
	xor	eax, eax
	pxor	xmm0, xmm0
	movss	DWORD PTR [rbp-12], xmm0
	lea	rax, [rbp-12]
	mov	rsi, rax
	mov	edi, OFFSET FLAT:.LC1
	mov	eax, 0
	call	__isoc99_scanf
	movss	xmm0, DWORD PTR [rbp-12]
	cvtss2sd	xmm0, xmm0
	mov	edi, OFFSET FLAT:.LC2
	mov	eax, 1
	call	printf
	mov	eax, 0
	mov	rdx, QWORD PTR [rbp-8]
	xor	rdx, QWORD PTR fs:40
	je	.L3
	call	__stack_chk_fail
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
