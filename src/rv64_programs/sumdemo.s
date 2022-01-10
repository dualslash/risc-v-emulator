	.file	"sumdemo.c"
	.text
	.align	2
	.type	sum_array, @function
sum_array:
	add	sp,sp,-48
	sd	s0,40(sp)
	add	s0,sp,48
	sw	a0,-36(s0)
	sd	a1,-48(s0)
	sw	zero,-24(s0)
	sw	zero,-20(s0)
	j	.L2
.L3:
	lw	a5,-20(s0)
	sll	a5,a5,2
	ld	a4,-48(s0)
	add	a5,a4,a5
	lw	a5,0(a5)
	lw	a4,-24(s0)
	addw	a5,a4,a5
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	addw	a5,a5,1
	sw	a5,-20(s0)
.L2:
	lw	a4,-20(s0)
	lw	a5,-36(s0)
	blt	a4,a5,.L3
	lw	a5,-24(s0)
	mv	a0,a5
	ld	s0,40(sp)
	add	sp,sp,48
	jr	ra
	.size	sum_array, .-sum_array
	.data
	.align	3
	.type	values, @object
	.size	values, 24
values:
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
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
	lui	a5,%hi(values)
	add	a1,a5,%lo(values)
	li	a0,6
	call	sum_array
	sw	a0,-20(s0)
	lw	a0,-20(s0)
	call	print_roman
	mv	a5,zero
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	add	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 5.2.0"
