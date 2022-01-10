	.text
        .align 4
	.globl	_start
	.type	_start, @function
main:
sub x20,x20,x19
blt x18,x20,main
jr ra
_start:
  li x18,1024
  li x19,128
  li x20,2048
  sll x19,x19,1
  call main
