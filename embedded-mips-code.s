    .data
    ctrl:   .asciiz "'fuck\n"

    .text
__malloc:
    lw $a0, ($sp)
    li $v0, 9
    syscall
    lw $t1, ($v0)
    sw $t1, 8($sp)
    jr $ra

__printf_one:
    li $v0, 4
    lw $a0, ($sp)
    syscall
    jr $ra

__printf:                   # {{{
##  lw $t0, ($sp)
##  mul $t1, $t0, 4
##  add $t1, $t1, $sp
##  sub $t2, $t1, 4
##  lw $t1, ($t1)
##  add $t1, $t1, -1
    lw $t1, ($sp)
    add $t1, $t1, -1
    add $t2, $sp, 4

    __printf_loop:
        add $t1, $t1, 1
        lb $t3, ($t1)
        beq $t3, 0, __printf_end
        beq $t3, '%', __printf_format           # %04d, %d, %c, %s, %04d <-> only positve integer
        beq $t3, '\\', __printf_trans            # \n, \t

        __printf_normal:
            li $v0, 11
            lb $a0, ($t1)
            syscall
            j __printf_loop

        __printf_format:
            lb $t4, 1($t1)
            beq $t4, 'd', __printf_format_d
            beq $t4, 'c', __printf_format_c
            beq $t4, 's', __printf_format_s
            beq $t4, '0', __printf_format_04d
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
                lw $t3, ($t2)
                bge $t3, 1000, __printf_format_04d_1000
                li $v0, 11
                li $a0, '0'
                syscall
                __printf_format_04d_1000:
                bge $t3, 100, __printf_format_04d_100
                li $v0, 11
                li $a0, '0'
                syscall
                __printf_format_04d_100:
                bge $t3, 10, __printf_format_04d_10
                li $v0, 11
                li $a0, '0'
                syscall
                __printf_format_04d_10:
                li $v0, 1
                move $a0, $t3
                syscall
            __printf_format_cont:
                add $t2, $t2, 4                 # even CHAR would be align to 4 bytes
                add $t1, $t1, 1
                j __printf_loop

        __printf_trans:
            li $v0, 11
            lb $a0, 1($t1)
            syscall
            add $t1, $t1, 1
            j __printf_loop

    __printf_end:
        jr $ra              #}}}

main:

#################
# test __printf #
#################
    sub $sp, $sp, 4         # ctrl
    la $t0, ctrl
    sw $t0, ($sp)
    jal __printf
    add $sp, $sp, 4

#################
# test __malloc #
#################
#   sub $sp, $sp, 4
#   sub $sp, $sp, 4
#   li $t0, 8
#   sw $t0, ($sp)
#   move $s0, $fp
#   move $fp, $sp
#   jal __malloc
#   move $fp, $s0
#   add $sp, $sp, 4
#   move $t0, $sp
#   li $t1, 0
#   sw $t1, ($t0)
#   li $t1, 1
#   sw $t1, 4($t0)
#   li $v0, 1
#   lw $a0, ($t0)
#   syscall
#   li $v0, 1
#   lw $a0, 4($t0)
#   syscall

    li $v0, 10
    syscall
