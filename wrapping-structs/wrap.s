	.text
	.file	"wrap.bc"
	.globl	add
	.align	16, 0x90
	.type	add,@function
add:                                    # @add
	.cfi_startproc
# BB#0:                                 # %param
	movw	(%rdi), %ax
	addw	2(%rdi), %ax
	movw	%ax, 4(%rdi)
	retq
.Ltmp0:
	.size	add, .Ltmp0-add
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
