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

    # Compare loaded data with stored data
    li a7, 0x12345678   # Load expected data to a7

    # Check byte load
    beq a3, a2, _pass_byte
    j _fail_byte

    _pass_byte:
    # Check half-word load
    beq a4, a2, _pass_halfword
    j _fail_halfword

    _pass_halfword:
    # Check word load
    beq a5, a2, _pass_word
    j _fail_word

    _pass_word:
    # Check double-word load
    beq a6, a2, _pass_doubleword
    j _fail_doubleword

    _pass_doubleword:
    li a0, 0            # Test passed
    j _exit

    _fail_byte:
    li a0, 1            # Test failed for byte load
    j _exit

    _fail_halfword:
    li a0, 2            # Test failed for half-word load
    j _exit

    _fail_word:
    li a0, 3            # Test failed for word load
    j _exit

    _fail_doubleword:
    li a0, 4            # Test failed for double-word load

_exit:
    # Exit
    ebreak
