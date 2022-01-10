	.file	"matvec.c"
	.data
	.align	3
	.type	A, @object
	.size	A, 256
A:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
	.word	3
	.word	3
	.word	3
	.word	3
	.word	3
	.word	4
	.word	4
	.word	4
	.word	4
	.word	4
	.word	4
	.word	4
	.word	4
	.word	5
	.word	5
	.word	5
	.word	5
	.word	5
	.word	5
	.word	5
	.word	5
	.word	6
	.word	6
	.word	6
	.word	6
	.word	6
	.word	6
	.word	6
	.word	6
	.word	7
	.word	7
	.word	7
	.word	7
	.word	7
	.word	7
	.word	7
	.word	7
	.word	8
	.word	8
	.word	8
	.word	8
	.word	8
	.word	8
	.word	8
	.word	8
	.align	3
	.type	B, @object
	.size	B, 32
B:
	.word	34
	.word	65
	.word	56
	.word	34
	.word	23
	.word	25
	.word	65
	.word	6
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	add	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	add	s0,sp,32
	sw	zero,-24(s0)
	j	.L2
.L5:
	sw	zero,-20(s0)
	j	.L3
.L4:
	lui	a5,%hi(A)
	lw	a4,-24(s0)
	lw	a3,-20(s0)
	sll	a3,a3,3
	add	a4,a3,a4
	sll	a4,a4,2
	add	a5,a5,%lo(A)
	add	a5,a4,a5
	lw	a4,0(a5)
	lui	a5,%hi(B)
	lw	a3,-20(s0)
	sll	a3,a3,2
	add	a5,a5,%lo(B)
	add	a5,a3,a5
	lw	a5,0(a5)
	addw	a4,a4,a5
	lui	a5,%hi(A)
	lw	a3,-24(s0)
	lw	a2,-20(s0)
	sll	a2,a2,3
	add	a3,a2,a3
	sll	a3,a3,2
	add	a5,a5,%lo(A)
	add	a5,a3,a5
	sw	a4,0(a5)
	lw	a5,-20(s0)
	addw	a5,a5,1
	sw	a5,-20(s0)
.L3:
	lw	a4,-20(s0)
	li	a5,7
	ble	a4,a5,.L4
	lw	a5,-24(s0)
	addw	a5,a5,1
	sw	a5,-24(s0)
.L2:
	lw	a4,-24(s0)
	li	a5,7
	ble	a4,a5,.L5
	sw	zero,-20(s0)
	j	.L6
.L7:
	lui	a4,%hi(A)
	lw	a5,-20(s0)
	sll	a5,a5,2
	sll	a3,a5,3
	add	a5,a5,a3
	add	a4,a4,%lo(A)
	add	a5,a5,a4
	lw	a5,0(a5)
	mv	a0,a5
	call	print_roman
	lw	a5,-20(s0)
	addw	a5,a5,1
	sw	a5,-20(s0)
.L6:
	lw	a4,-20(s0)
	li	a5,7
	ble	a4,a5,.L7
	mv	a5,zero
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	add	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 5.2.0"
