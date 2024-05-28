# Test Store and Load Instructions

.section .text
.globl _start

_start:
    # Initialize data
    li a1, 0x80001000       # Load base address of data section to a1
    li a2, 0x12345678   # Load data to be stored to a2

    # Store data
    sb a2, 0(a1)        # Store a byte (8 bits) of data to address a1
    sh a2, 2(a1)        # Store a half-word (16 bits) of data to address a1 + 2
    sw a2, 4(a1)        # Store a word (32 bits) of data to address a1 + 4
    sd a2, 8(a1)        # Store a double-word (64 bits) of data to address a1 + 8

    # Load data
    lb a3, 0(a1)        # Load a byte (8 bits) of data from address a1 to a3
    lh a4, 2(a1)        # Load a half-word (16 bits) of data from address a1 + 2 to a4
    lw a5, 4(a1)        # Load a word (32 bits) of data from address a1 + 4 to a5
    ld a6, 8(a1)        # Load a double-word (64 bits) of data from address a1 + 8 to a6
    
    bneq a3, a2, fail_exit # Check byte load
    bneq a4, a2, fail_exit # Check half-word load
    bneq a5, a2, fail_exit # Check word load
    bneq a6, a2, fail_exit # Check double-word load
    ebreak

fail_exit:
    ebreak


