	.file	"Load.c"
	.globl	_M
	.bss
	.align 32
_M:
	.space 400
	.comm	_IR, 4, 2
	.comm	_IC, 4, 2
	.comm	_C, 4, 2
	.comm	_R, 4, 2
	.comm	_buffer, 41, 5
	.comm	_SI, 4, 2
	.globl	_input
	.align 4
_input:
	.space 4
	.globl	_output
	.align 4
_output:
	.space 4
	.section .rdata,"dr"
LC0:
	.ascii "M[%d] : |%c|%c|%c|%c|\12\0"
	.text
	.globl	_memdump
	.def	_memdump;	.scl	2;	.type	32;	.endef
_memdump:
LFB17:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$52, %esp
	.cfi_offset 3, -12
	movl	$0, -12(%ebp)
	jmp	L2
L3:
	movl	-12(%ebp), %eax
	movzbl	_M+3(,%eax,4), %eax
	movsbl	%al, %ebx
	movl	-12(%ebp), %eax
	movzbl	_M+2(,%eax,4), %eax
	movsbl	%al, %ecx
	movl	-12(%ebp), %eax
	movzbl	_M+1(,%eax,4), %eax
	movsbl	%al, %edx
	movl	-12(%ebp), %eax
	movzbl	_M(,%eax,4), %eax
	movsbl	%al, %eax
	movl	%ebx, 20(%esp)
	movl	%ecx, 16(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	addl	$1, -12(%ebp)
L2:
	cmpl	$49, -12(%ebp)
	jle	L3
	nop
	addl	$52, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE17:
	.globl	_readIR
	.def	_readIR;	.scl	2;	.type	32;	.endef
_readIR:
LFB18:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)
	jmp	L5
L6:
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-4(%ebp), %ecx
	movl	12(%ebp), %eax
	addl	%ecx, %eax
	movzbl	(%eax), %eax
	movb	%al, (%edx)
	addl	$1, -4(%ebp)
L5:
	cmpl	$3, -4(%ebp)
	jle	L6
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE18:
	.globl	_init
	.def	_init;	.scl	2;	.type	32;	.endef
_init:
LFB19:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)
	jmp	L8
L9:
	movl	-4(%ebp), %eax
	movb	$32, _M(,%eax,4)
	movl	-4(%ebp), %eax
	movb	$32, _M+1(,%eax,4)
	movl	-4(%ebp), %eax
	movb	$32, _M+2(,%eax,4)
	movl	-4(%ebp), %eax
	movb	$32, _M+3(,%eax,4)
	addl	$1, -4(%ebp)
L8:
	cmpl	$99, -4(%ebp)
	jle	L9
	movl	$0, -8(%ebp)
	jmp	L10
L11:
	movl	-8(%ebp), %eax
	addl	$_buffer, %eax
	movb	$0, (%eax)
	addl	$1, -8(%ebp)
L10:
	cmpl	$40, -8(%ebp)
	jle	L11
	movl	$0, -12(%ebp)
	jmp	L12
L13:
	movl	-12(%ebp), %eax
	addl	$_IR, %eax
	movb	$32, (%eax)
	movl	-12(%ebp), %eax
	addl	$_R, %eax
	movb	$32, (%eax)
	addl	$1, -12(%ebp)
L12:
	cmpl	$3, -12(%ebp)
	jle	L13
	movl	$0, _IC
	movl	$0, _C
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE19:
	.section .rdata,"dr"
LC1:
	.ascii "$AMJ\0"
LC2:
	.ascii "$DTA\0"
LC3:
	.ascii "$END\0"
LC4:
	.ascii "\12END\12 \0"
	.text
	.globl	_LOAD
	.def	_LOAD;	.scl	2;	.type	32;	.endef
_LOAD:
LFB20:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	movl	$0, -12(%ebp)
	movl	$0, -16(%ebp)
	jmp	L15
L25:
	movl	$0, -28(%ebp)
	movl	$LC1, 4(%esp)
	movl	$_buffer, (%esp)
	call	_strstr
	movl	%eax, -28(%ebp)
	cmpl	$0, -28(%ebp)
	je	L16
	call	_init
	movl	$1, -12(%ebp)
	jmp	L15
L16:
	movl	$LC2, 4(%esp)
	movl	$_buffer, (%esp)
	call	_strstr
	movl	%eax, -28(%ebp)
	cmpl	$0, -28(%ebp)
	je	L17
	movl	$0, -12(%ebp)
	call	_SE
	jmp	L18
L17:
	movl	$LC3, 4(%esp)
	movl	$_buffer, (%esp)
	call	_strstr
	movl	%eax, -28(%ebp)
	cmpl	$0, -28(%ebp)
	je	L18
	movl	$LC4, (%esp)
	call	_printf
L18:
	cmpl	$0, -12(%ebp)
	je	L15
	movl	$_buffer, -20(%ebp)
	jmp	L19
L24:
	movl	-20(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$72, %al
	je	L20
	movl	$4, %eax
	jmp	L21
L20:
	movl	$1, %eax
L21:
	movl	%eax, -32(%ebp)
	movl	$0, -24(%ebp)
	jmp	L22
L23:
	movl	-20(%ebp), %eax
	movzbl	(%eax), %eax
	movl	-16(%ebp), %edx
	leal	0(,%edx,4), %ecx
	movl	-24(%ebp), %edx
	addl	%ecx, %edx
	addl	$_M, %edx
	movb	%al, (%edx)
	addl	$1, -24(%ebp)
	addl	$1, -20(%ebp)
L22:
	movl	-24(%ebp), %eax
	cmpl	-32(%ebp), %eax
	jl	L23
	addl	$1, -16(%ebp)
L19:
	movl	-20(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$10, %al
	jne	L24
L15:
	movl	_input, %eax
	movl	%eax, 8(%esp)
	movl	$41, 4(%esp)
	movl	$_buffer, (%esp)
	call	_fgets
	testl	%eax, %eax
	jne	L25
	call	_memdump
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE20:
	.globl	_READ
	.def	_READ;	.scl	2;	.type	32;	.endef
_READ:
LFB21:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movzbl	_IR+2, %eax
	movsbl	%al, %eax
	leal	-48(%eax), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, %edx
	movzbl	_IR+3, %eax
	movsbl	%al, %eax
	subl	$48, %eax
	addl	%edx, %eax
	movl	%eax, -12(%ebp)
	movl	_input, %eax
	movl	%eax, 8(%esp)
	movl	$41, 4(%esp)
	movl	$_buffer, (%esp)
	call	_fgets
	movl	$_buffer, -16(%ebp)
	jmp	L27
L32:
	movl	$0, -20(%ebp)
	jmp	L28
L31:
	movl	-16(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -16(%ebp)
	movzbl	(%eax), %eax
	movl	-12(%ebp), %edx
	leal	0(,%edx,4), %ecx
	movl	-20(%ebp), %edx
	addl	%ecx, %edx
	addl	$_M, %edx
	movb	%al, (%edx)
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$10, %al
	je	L33
	addl	$1, -20(%ebp)
L28:
	cmpl	$3, -20(%ebp)
	jle	L31
	jmp	L30
L33:
	nop
L30:
	addl	$1, -12(%ebp)
L27:
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$10, %al
	jne	L32
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE21:
	.globl	_WRITE
	.def	_WRITE;	.scl	2;	.type	32;	.endef
_WRITE:
LFB22:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movzbl	_IR+2, %eax
	movsbl	%al, %eax
	leal	-48(%eax), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, %edx
	movzbl	_IR+3, %eax
	movsbl	%al, %eax
	subl	$48, %eax
	addl	%edx, %eax
	movl	%eax, -20(%ebp)
	movl	$0, -12(%ebp)
	movl	-20(%ebp), %eax
	movl	%eax, -16(%ebp)
	jmp	L35
L36:
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	-16(%ebp), %edx
	movzbl	_M(,%edx,4), %edx
	movb	%dl, _buffer(%eax)
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	-16(%ebp), %edx
	movzbl	_M+1(,%edx,4), %edx
	movb	%dl, _buffer(%eax)
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	-16(%ebp), %edx
	movzbl	_M+2(,%edx,4), %edx
	movb	%dl, _buffer(%eax)
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	-16(%ebp), %edx
	movzbl	_M+3(,%edx,4), %edx
	movb	%dl, _buffer(%eax)
	addl	$1, -16(%ebp)
L35:
	movl	-20(%ebp), %eax
	addl	$10, %eax
	cmpl	-16(%ebp), %eax
	jg	L36
	movl	-12(%ebp), %eax
	addl	$_buffer, %eax
	movb	$10, (%eax)
	movl	_output, %eax
	movl	%eax, 4(%esp)
	movl	$_buffer, (%esp)
	call	_fputs
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE22:
	.globl	_TERMINATE
	.def	_TERMINATE;	.scl	2;	.type	32;	.endef
_TERMINATE:
LFB23:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE23:
	.globl	_LoadR
	.def	_LoadR;	.scl	2;	.type	32;	.endef
_LoadR:
LFB24:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE24:
	.globl	_StoreR
	.def	_StoreR;	.scl	2;	.type	32;	.endef
_StoreR:
LFB25:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE25:
	.globl	_compare
	.def	_compare;	.scl	2;	.type	32;	.endef
_compare:
LFB26:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE26:
	.globl	_MOS
	.def	_MOS;	.scl	2;	.type	32;	.endef
_MOS:
LFB27:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	_SI, %eax
	cmpl	$1, %eax
	jne	L42
	call	_READ
	jmp	L45
L42:
	movl	_SI, %eax
	cmpl	$2, %eax
	jne	L44
	call	_WRITE
	jmp	L45
L44:
	movl	_SI, %eax
	cmpl	$3, %eax
	jne	L45
	call	_TERMINATE
L45:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE27:
	.section .rdata,"dr"
LC5:
	.ascii "%d\0"
LC6:
	.ascii "Memoety exceeded\0"
	.text
	.globl	_EUP
	.def	_EUP;	.scl	2;	.type	32;	.endef
_EUP:
LFB28:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	_IC, %eax
	sall	$2, %eax
	addl	$_M, %eax
	movl	%eax, 4(%esp)
	movl	$_IR, (%esp)
	call	_readIR
	movl	_IC, %eax
	addl	$1, %eax
	movl	%eax, _IC
	movl	_IC, %eax
	movl	%eax, 4(%esp)
	movl	$LC5, (%esp)
	call	_printf
	movl	_IC, %eax
	cmpl	$6, %eax
	jne	L47
	movl	$LC6, (%esp)
	call	_printf
	jmp	L46
L47:
	movl	$0, _SI
	movzbl	_IR, %eax
	movsbl	%al, %eax
	cmpl	$72, %eax
	je	L50
	cmpl	$80, %eax
	je	L51
	cmpl	$71, %eax
	jne	L49
	movl	$1, _SI
	call	_MOS
	jmp	L49
L51:
	movl	$2, _SI
	call	_MOS
	jmp	L49
L50:
	movl	$3, _SI
	call	_MOS
	nop
L49:
	call	_EUP
L46:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE28:
	.section .rdata,"dr"
	.align 4
LC7:
	.ascii "jaljakdjflasjdfklajsdflkdslfjadsljfldsk\0"
	.text
	.globl	_SE
	.def	_SE;	.scl	2;	.type	32;	.endef
_SE:
LFB29:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$LC7, (%esp)
	call	_printf
	movl	$0, _IC
	call	_EUP
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE29:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC8:
	.ascii "r\0"
LC9:
	.ascii "input.txt\0"
LC10:
	.ascii "w\0"
LC11:
	.ascii "output.txt\0"
LC12:
	.ascii "The file is not opened\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB30:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	movl	$LC8, 4(%esp)
	movl	$LC9, (%esp)
	call	_fopen
	movl	%eax, _input
	movl	$LC10, 4(%esp)
	movl	$LC11, (%esp)
	call	_fopen
	movl	%eax, _output
	movl	_input, %eax
	testl	%eax, %eax
	je	L55
	movl	_output, %eax
	testl	%eax, %eax
	jne	L56
L55:
	movl	$LC12, (%esp)
	call	_printf
	movl	$0, (%esp)
	call	_exit
L56:
	call	_LOAD
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE30:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_strstr;	.scl	2;	.type	32;	.endef
	.def	_fgets;	.scl	2;	.type	32;	.endef
	.def	_fputs;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_exit;	.scl	2;	.type	32;	.endef
