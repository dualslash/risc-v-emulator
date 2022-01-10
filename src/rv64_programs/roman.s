	.file	"roman.c"
	.data
	.align	3
	.type	roman_table, @object
	.size	roman_table, 64
roman_table:
	.word	1000
	.byte	77
	.zero	3
	.word	500
	.byte	68
	.zero	3
	.word	100
	.byte	67
	.zero	3
	.word	50
	.byte	76
	.zero	3
	.word	10
	.byte	88
	.zero	3
	.word	5
	.byte	86
	.zero	3
	.word	1
	.byte	73
	.zero	3
	.word	0
	.byte	0
	.zero	3
	.text
	.align	2
	.globl	print_roman
	.type	print_roman, @function
print_roman:
	add	sp,sp,-48
	sd	s0,40(sp)
	add	s0,sp,48
	sw	a0,-36(s0)
	li	a5,512
	sd	a5,-32(s0)
	sw	zero,-20(s0)
	j	.L2
.L4:
	lui	a4,%hi(roman_table)
	lw	a5,-20(s0)
	add	a4,a4,%lo(roman_table)
	sll	a5,a5,3
	add	a5,a4,a5
	lbu	a4,4(a5)
	ld	a5,-32(s0)
	sb	a4,0(a5)
	lui	a5,%hi(roman_table)
	lw	a4,-20(s0)
	sll	a4,a4,3
	add	a5,a5,%lo(roman_table)
	add	a5,a4,a5
	lw	a5,0(a5)
	lw	a4,-36(s0)
	subw	a5,a4,a5
	sw	a5,-36(s0)
.L3:
	lui	a5,%hi(roman_table)
	lw	a4,-20(s0)
	sll	a4,a4,3
	add	a5,a5,%lo(roman_table)
	add	a5,a4,a5
	lw	a4,0(a5)
	lw	a5,-36(s0)
	ble	a4,a5,.L4
	lw	a5,-20(s0)
	addw	a5,a5,1
	sw	a5,-20(s0)
.L2:
	lui	a5,%hi(roman_table)
	lw	a4,-20(s0)
	sll	a4,a4,3
	add	a5,a5,%lo(roman_table)
	add	a5,a4,a5
	lw	a5,0(a5)
	bnez	a5,.L3
	ld	a5,-32(s0)
	li	a4,10
	sb	a4,0(a5)
	nop
	ld	s0,40(sp)
	add	sp,sp,48
	jr	ra
	.size	print_roman, .-print_roman
	.ident	"GCC: (GNU) 5.2.0"
