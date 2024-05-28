# Test Store and Load Instructions
.section .data
array:
    .align 4
    .word 0x11111111, 0x22222222, 0x33333333 # global variable, should be put into ram.
    # .word 0x00000000, 0x00000000, 0x00000000 # global variable, should be put into ram.
string1:
    .string "Test Passed!\n"
string2:
    .string "Test Failed!\n"

.section .text
# .globl _start
.globl main



# _start:
main:
    la a1, array        # Load base address of data section to a1

    # Store data
    li a2, 0xaabbccdd   # word stored in machine from low to high addr is 0xaa, 0xbb, 0xcc, 0xdd 
    sb a2, 0(a1)        # Store a byte (8 bits) of data to address a1
    li a2, 0xbbccddee
    sh a2, 4(a1)        # Store a half-word (16 bits) of data to address a1 + 2
    li a2, 0xccddeeff
    sw a2, 8(a1)        # Store a word (32 bits) of data to address a1 + 4

    # Load data
    lbu a3, 0(a1)
    li  a2, 0xdd
    bne a3, a2, fail_exit # Check byte load

    lhu a3, 4(a1)
    li  a2, 0xddee
    bne a3, a2, fail_exit # Check half-word load

    lw  a3, 0(a1)
    li  a2, 0x111111dd
    # li  a2, 0x000000dd
    bne a3, a2, fail_exit # Check byte load

    lw  a3, 4(a1)
    li  a2, 0x2222ddee
    # li  a2, 0x0000ddee
    bne a3, a2, fail_exit # Check half-word load

    lw  a3, 8(a1)
    li  a2, 0xccddeeff
    bne a3, a2, fail_exit # Check word load

    # output pass information
    la  a1, string1
    jal output_info    # output information

    ebreak

fail_exit:
    la  a1, string2
    jal output_info    # output information

    ebreak

output_info:
    # li a2, 0xa00003f8 # serial address
    li a2, 0x10000000 # serial address
    li a3, 13         # the length of string
loop:
    lbu  a4, 0(a1)
    sb   a4, 0(a2)
    addi a1, a1, 1
    addi a3, a3, -1
    bnez a3, loop

    ret