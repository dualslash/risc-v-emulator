	.text
        .align 4
	.globl	_start
	.type	_start, @function
_start:
  sd x18,1024(ra)
  lw x19,1024(ra)
  lb x20,1024(ra)
