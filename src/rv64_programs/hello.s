	.file	"hello.c"
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	add	sp,sp,-32
	sd	s0,24(sp)
	add	s0,sp,32
	li	a5,512
	sd	a5,-24(s0)
	ld	a5,-24(s0)
	li	a4,104
	sb	a4,0(a5)
	ld	a5,-24(s0)
	li	a4,101
	sb	a4,0(a5)
	ld	a5,-24(s0)
	li	a4,108
	sb	a4,0(a5)
	ld	a5,-24(s0)
	li	a4,108
	sb	a4,0(a5)
	ld	a5,-24(s0)
	li	a4,111
	sb	a4,0(a5)
	ld	a5,-24(s0)
	li	a4,10
	sb	a4,0(a5)
	mv	a5,zero
	mv	a0,a5
	ld	s0,24(sp)
	add	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 5.2.0"
