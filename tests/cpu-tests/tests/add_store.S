# Test case: Add two numbers and store the result in a register
.global main

main:
# Set the initial values of the input operands
li x1, 5
li x2, 7

# Perform the addition operation
add x5, x1, x2

# Store the result in a register
mv x4, x5

# Halt the processor
ebreak
