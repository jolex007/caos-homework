	.file	"tests.c"
	.intel_syntax noprefix
	.text
	.globl	shrink
	.type	shrink, @function
shrink:
.LFB0:
	.cfi_startproc
	mov	rax, QWORD PTR A[rip]
	mov	eax, DWORD PTR [rax+rdi*4]
	mov	DWORD PTR -4[rsp], eax
	ret
	.cfi_endproc
.LFE0:
	.size	shrink, .-shrink
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
