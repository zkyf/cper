.data
temp: .space 40
var0: .space 4
var1: .asciiz "helloword\n"
.align 2

.text
__malloc:
lw $a0, ($sp)
li $v0, 9
syscall
sw $v0, 8($sp)
jr $ra

__printf_one:
li $v0, 4
lw $a0, ($sp)
syscall
jr $ra

__printf:
add $t2, $sp, 4
lw $t1, ($sp)
add $t1, $t1, -1
__printf_loop:
add $t1, $t1, 1
lb $a2, ($t1)
beq $a2, 0, __printf_end
beq $a2, '%', __printf_format           # %04d, %d, %c, %s, %04d <-> only positve integer
beq $a2, '\\', __printf_trans            # \n, \t
__printf_normal:
li $v0, 11
lb $a0, ($t1)
syscall
j __printf_loop
__printf_format:
lb $t0, 1($t1)
beq $t0, 'd', __printf_format_d
beq $t0, 'c', __printf_format_c
beq $t0, 's', __printf_format_s
beq $t0, '0', __printf_format_04d
j __printf_normal
__printf_format_d:
li $v0, 1
lw $a0, ($t2)
syscall
j __printf_format_cont
__printf_format_c:
li $v0, 11
lb $a0, ($t2)
syscall
j __printf_format_cont
__printf_format_s:
li $v0, 4
lw $a0, ($t2)
syscall
j __printf_format_cont
__printf_format_04d:
add $t1, $t1, 2
lw $a2, ($t2)
bge $a2, 1000, __printf_format_04d_1000
li $v0, 11
li $a0, '0'
syscall
__printf_format_04d_1000:
bge $a2, 100, __printf_format_04d_100
li $v0, 11
li $a0, '0'
syscall
__printf_format_04d_100:
bge $a2, 10, __printf_format_04d_10
li $v0, 11
li $a0, '0'
syscall
__printf_format_04d_10:
li $v0, 1
move $a0, $a2
syscall
__printf_format_cont:
add $t2, $t2, 4
add $t1, $t1, 1
j __printf_loop
__printf_trans:
li $v0, 11
lb $a0, 1($t1)
syscall
add $t1, $t1, 1
j __printf_loop
__printf_end:
jr $ra

main:
la $a3, temp
la $t0, var0
sw $t0, 8($a3)
la $t0, var1
sw $t0, 24($a3)
li $8, 3
sw $8, 12($a3)
lw $8, 12($a3)
lw $9, 8($a3)
sw $8, 0($9)
lw $11, 24($a3)
move $12, $11
add $11, $29, -28
sw $12, 0($11)
add $29, $29, -28
jal __printf_one
sub $29, $29, -28
add $11, $29, 4
lw $13, 8($a3)
lw $12, 0($13)
sw $12, 0($11)
j __program_end
j __program_end
__program_end:
li $v0, 10
syscall
