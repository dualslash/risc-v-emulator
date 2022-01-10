	.text
        .align 4
	.globl	_start
	.type	_start, @function
_start:
  li x18,0xff
  andi x19,x18,0x0f
  and x20,x18,0xf0
