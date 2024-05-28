# Test dcache pipeline, if the instructions can be execute pipelined in lsu module.
.section .data
array:
    .word 0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555, 0x66666666, 0x77777777, 0x88888888


.section .text
.globl _start

_start:
    # Initialize data
    la a1, array       # Load base address of data section to a1
    li a2, 0x12345678   # Load data to be stored to a2

    # Store data
    sb a2, 0(a1)        # Store a byte (8 bits) of data to address a1
    sh a2, 4(a1)        # Store a half-word (16 bits) of data to address a1 + 2
    sw a2, 8(a1)        # Store a word (32 bits) of data to address a1 + 4
    sw a2, 12(a1)
    sw a2, 16(a1)
    sw a2, 20(a1)
    sw a2, 24(a1)
    sw a2, 28(a1)

    # Load data
    lw tp, 28(a1)
    lw s1, 24(a1)
    lw s0, 20(a1)
    lw a0, 16(a1)
    lw t2, 12(a1)
    lw t1, 8(a1)        # Load a word (32 bits) of data from address a1 + 4 to a5
    lw t0, 4(a1)
    lh a5, 4(a1)        # Load a half-word (16 bits) of data from address a1 + 2 to a4
    lw a4, 0(a1)
    lb a3, 0(a1)        # Load a byte (8 bits) of data from address a1 to a3
    
    ebreak