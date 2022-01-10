        .comm   _stack,4096,8
        .text
        .align 2
        .extern _gp
	.globl _start
        .type _start, @function
_start:
        # Initialize gp
        la      gp,_gp
        # create a pseudo-stack.
        lui     sp,%hi(_stack+4096)
        add     sp,sp,%lo(_stack+4096)
        add     sp,sp,-16

        call main

        # end simulation with exit code
        sw      a0,632(zero)
        nop
        nop
        nop
        nop
        nop
        nop
        .size   _start, .-_start
