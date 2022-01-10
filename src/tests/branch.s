	.text
        .align 4
	.globl	_start
	.type	_start, @function
.L1:
  li x18,0
  j _start
.L2:
  li x19,1024
  j _start
.L3:
  li x20,1024
  j _end
_start:
  bnez x18,.L1
  ble x19,x20,.L2
  blt x20,x19,.L3
_end:
