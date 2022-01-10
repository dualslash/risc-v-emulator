	.text
        .align 4
	.globl	_start
	.type	_start, @function
_start:
	add 	x1,x1,x2
	add 	x1,x1,x3
	add 	x1,x1,x4
	add 	x1,x1,x5
	add 	x1,x1,x2
	add 	x1,x1,x3
	add 	x1,x1,x4
	add 	x1,x1,x5
	.size	_start, .-_start
