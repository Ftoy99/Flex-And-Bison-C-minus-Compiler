.data
newln: .asciiz  "\n" 
a: .space 4
    .align 2
b: .space 4
    .align 2
c: .space 4
    .align 2
Table: .space 80
    .align 2
.text
.globl main
la $t0 a
la $t1 b
la $t2 c
la $t3 Table
average:
add $t4 $t-1 $t-1
main:
li $t0 1
li $t1 2
add $t5 $t0 $t1
move $t2 $t5
jal Average
move $t2 $t5
li $t0 0
li $t1 0
li $t2 0
bne a, $t1, _l2
li $t0 1
j _l3
_l2:
li $t0 2
_l3:
move $t2 $t0
li $v0, 10
