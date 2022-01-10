	.file	"hellof.c"
	.text
	.align	2
	.globl	putchar
	.type	putchar, @function
putchar:
	add	sp,sp,-48
	sd	s0,40(sp)
	add	s0,sp,48
	sw	a0,-36(s0)
	li	a5,512
	sd	a5,-24(s0)
	lw	a5,-36(s0)
	and	a4,a5,0xff
	ld	a5,-24(s0)
	sb	a4,0(a5)
	mv	a5,zero
	mv	a0,a5
	ld	s0,40(sp)
	add	sp,sp,48
	jr	ra
	.size	putchar, .-putchar
	.align	2
	.globl	puts
	.type	puts, @function
puts:
	add	sp,sp,-48
	sd	ra,40(sp)
	sd	s0,32(sp)
	add	s0,sp,48
	sd	a0,-40(s0)
	ld	a5,-40(s0)
	sd	a5,-24(s0)
	j	.L4
.L5:
	ld	a5,-24(s0)
	lbu	a5,0(a5)
	mv	a0,a5
	call	putchar
	ld	a5,-24(s0)
	add	a5,a5,1
	sd	a5,-24(s0)
.L4:
	ld	a5,-24(s0)
	lbu	a5,0(a5)
	bnez	a5,.L5
	li	a0,10
	call	putchar
	nop
	ld	ra,40(sp)
	ld	s0,32(sp)
	add	sp,sp,48
	jr	ra
	.size	puts, .-puts
	.section	.rodata
	.align	3
.LC0:
	.string	"hello"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	add	sp,sp,-16
	sd	ra,8(sp)
	sd	s0,0(sp)
	add	s0,sp,16
	lui	a5,%hi(.LC0)
	add	a0,a5,%lo(.LC0)
	call	puts
	mv	a5,zero
	mv	a0,a5
	ld	ra,8(sp)
	ld	s0,0(sp)
	add	sp,sp,16
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 5.2.0"
