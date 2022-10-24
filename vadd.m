lui x7, 0x400
lui x7, 0x800
lui x7, 0xC00
lui x0, 0x00
sw 0x00, sp
lw x1, sp
slli x1, 2
add x2, x7, x1
lw x3, x2
add x2, x8, x1
lw x4, x2
add x2, x9, x1
add x5, x3, x4
sw x5, x2
srli x1, x1, 2
addi x6, x1, 1
sw x6, sp
lui x0, 255
bge x6, x0, -56
RET (JALR x0,x1,0)