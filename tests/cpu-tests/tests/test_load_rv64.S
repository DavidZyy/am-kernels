.data
    # Static data at memory address 0x1000
    .align 4
# data_byte:  .byte 0x12
data_byte:  .half 0x12
data_half:  .half 0x3456
data_word:  .word 0x789ABCDE
data_double:  .dword 0x123456789ABCDEF0

.text
.globl _start

_start:
    la a1, data_byte    # Load address of byte data into a1

    lb a0, 0(a1)        # Load byte from address in a1, store in a0

    la a1, data_half    # Load address of halfword data into a1

    lh a2, 0(a1)        # Load halfword from address in a1, store in a2

    la a1, data_word    # Load address of word data into a1

    lw a3, 0(a1)        # Load word from address in a1, store in a3

    la a1, data_double  # Load address of doubleword data into a1

    ld a4, 0(a1)        # Load doubleword from address in a1, store in a4

    # Test results
    # a0 = byte loaded from memory
    # a2 = halfword loaded from memory
    # a3 = word loaded from memory
    # a4 = doubleword loaded from memory

    # Test cases
    li a5, 0x12         # Expected value of byte loaded from memory
    li a6, 0x3456       # Expected value of halfword loaded from memory
    li a7, 0x789ABCDE   # Expected value of word loaded from memory
#    ld a8, data_double  # Expected value of doubleword loaded from memory

    bne a0, a5, _fail_byte   # Check if loaded byte matches expected value
    bne a2, a6, _fail_halfword   # Check if loaded halfword matches expected value
    bne a3, a7, _fail_word   # Check if loaded word matches expected value
    # bne a4, a8, _fail_doubleword   # Check if loaded doubleword matches expected value

    j _pass          # Jump to pass label

_fail_byte:
    li a0, 1          # Set a0 to indicate test failure
    j _end             # Jump to end of testcase

_fail_halfword:
    li a0, 2          # Set a0 to indicate test failure
    j _end             # Jump to end of testcase

_fail_word:
    li a0, 3          # Set a0 to indicate test failure
    j _end             # Jump to end of testcase

_fail_doubleword:
    li a0, 4          # Set a0 to indicate test failure
    j _end             # Jump to end of testcase

_pass:
    li a0, 0           # Set a0 to indicate test pass
    ebreak

_end:
    # End of testcase
    # You can add any cleanup or exit code here
