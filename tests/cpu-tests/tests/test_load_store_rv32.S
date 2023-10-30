.section .data
    .align 4
value1:
    .word 0x12345678   # Value to be stored and loaded

value2:
    .word 0xdeadbeef   # Another value for testing

value3:
    .word 0xcafebabe   # Yet another value

.section .bss
    .align 4

buffer:
    .space 16          # Allocate space for data

.section .text
.globl _start

_start:
    # Initialize data addresses
    la a0, value1       # Load the address of 'value1' into a0
    la a1, value2       # Load the address of 'value2' into a1
    la a2, value3       # Load the address of 'value3' into a2
    la a3, buffer       # Load the address of 'buffer' into a3

    # Store data using different instructions and addressing modes
    li a4, 0xabcdefab   # Value to store
    sw a4, 0(a0)        # Store a word (32 bits) to the address pointed by a0
    sh a4, 4(a1)        # Store a half-word (16 bits) to the address pointed by a1 + 4
    sb a4, 8(a2)        # Store a byte (8 bits) to the address pointed by a2 + 8

    # Load data using different instructions and addressing modes
    lw a5, 0(a0)        # Load a word (32 bits) from the address pointed by a0 to a5

    # Compare loaded data with stored data
    beq a4, a5, _pass_word
    j _fail_word

_pass_word:
    # Check half-word load
    j _fail_halfword

_pass_halfword:
    # Check byte load
    j _fail_byte

_pass_byte:
    # Test passed
    li a0, 0
    j _exit

_fail_word:
    # Test failed for word load
    li a0, 1
    j _exit

_fail_halfword:
    # Test failed for half-word load
    li a0, 2
    j _exit

_fail_byte:
    # Test failed for byte load
    li a0, 3

_exit:
    # Exit
    ebreak
