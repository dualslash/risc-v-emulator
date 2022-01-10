	.file	"comp.c"
	.comm	A,80,8
	.comm	B,80,8
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	add	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	add	s0,sp,32
	sw	zero,-20(s0)
	j	.L2
.L3:
	lui	a5,%hi(B)
	lw	a4,-20(s0)
	sll	a4,a4,2
	add	a5,a5,%lo(B)
	add	a5,a4,a5
	lw	a4,-20(s0)
	sw	a4,0(a5)
	lw	a5,-20(s0)
	addw	a5,a5,1
	sw	a5,-20(s0)
.L2:
	lw	a4,-20(s0)
	li	a5,19
	ble	a4,a5,.L3
	li	a5,42
	sw	a5,-24(s0)
	li	a5,1
	sw	a5,-20(s0)
	j	.L4
.L5:
	lw	a5,-20(s0)
	addw	a4,a5,-1
	lui	a5,%hi(B)
	sll	a4,a4,2
	add	a5,a5,%lo(B)
	add	a5,a4,a5
	lw	a4,0(a5)
	lw	a5,-24(s0)
	addw	a4,a4,a5
	lui	a5,%hi(A)
	lw	a3,-20(s0)
	sll	a3,a3,2
	add	a5,a5,%lo(A)
	add	a5,a3,a5
	sw	a4,0(a5)
	lw	a5,-20(s0)
	addw	a5,a5,1
	sw	a5,-20(s0)
.L4:
	lw	a4,-20(s0)
	li	a5,19
	ble	a4,a5,.L5
	lui	a5,%hi(A)
	add	a5,a5,%lo(A)
	lw	a5,76(a5)
	mv	a0,a5
	call	print_roman
	mv	a5,zero
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	add	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 5.2.0"
