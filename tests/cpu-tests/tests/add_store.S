# Test case: Add two numbers and store the result in a register
.global main

main:
# Set the initial values of the input operands
li x1, 1
li x2, 2
li x3, 3
li x4, 4
li x5, 5
li x6, 6
li x7, 7
li x8, 8
li x9, 9
li x10, 10
li x11, 11
li x12, 12

# Perform the addition operation
add x5, x1, x2

# Store the result in a register
mv x4, x5

# Halt the processor
ebreak
