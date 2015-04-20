	.text
	.file	"main.bc"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rax
.Ltmp0:
	.cfi_def_cfa_offset 16
	movl	$.Lstr, %edi
	callq	output
	popq	%rax
	retq
.Ltmp1:
	.size	main, .Ltmp1-main
	.cfi_endproc

	.type	.Lstr,@object           # @str
	.section	.rodata.str1.1,"aMS",@progbits,1
.Lstr:
	.asciz	"Hallo Welt!"
	.size	.Lstr, 12


	.section	".note.GNU-stack","",@progbits
